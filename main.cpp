#include <ctime>

#include "Month.h"
#include "FileHandler.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace ftxui;
using namespace std;


Elements getMonthContent(int mn, int yn){
    Elements monthContent;

    auto month = Month(mn, yn).toString();
    for(auto & i : month){
        monthContent.push_back(text(i));
    }
    return monthContent;
}

Elements getHolidaysContent(int mn, int yn, FileHandler &reader){
    Elements holidaysContent;
    vector<string> holidays;
    holidays = reader.getHolidaysFromFile(mn, yn);
    for(auto & i : holidays){
        holidaysContent.push_back(text(i));
    }
    return holidaysContent;
}

void mainUI() {
    string error = "";
    string delError = "";

    time_t now = time(0);
    tm* ltm = localtime(&now);

    int curYear = 1900 + ltm->tm_year;
    int curMon = 1 + ltm->tm_mon;
    auto monthContent = getMonthContent(curMon, curYear);

    string date = "";
    string holiday = "";
    string delDate = "";
    auto dateInput = Input(&date, "День");
    auto holidaysInput = Input(&holiday, "Праздник");
    auto delDateInput = Input(&delDate, "Дата для удаления");

    FileHandler holidayAdder = FileHandler("holidays.txt", FileHandler::OUT_MODE);
    FileHandler holidaysReader = FileHandler("holidays.txt", FileHandler::IN_MODE);

    auto holidaysContent = getHolidaysContent(curMon, curYear, holidaysReader);

    auto btnAdd = Button("Добавить", [&] {
        if(date.empty()) {
            error = "Введите число праздника";
            return;
        }
        if(!regex_match(date, regex("[0-9]+"))){
            error = "Дата должна быть числом!";
            return;
        }
        try {
            if(stoi(date) > 31) {
                error = "Слишком большая дата!";
            }else {
                holidayAdder.putHolidayToFile(stoi(date), curMon, curYear, holiday);
                holidaysContent = getHolidaysContent(curMon, curYear, holidaysReader);
                error = "";
            }
        }catch(const char* ex){
            error = ex;
        }

        date = "";
        holiday = "";
    });

    auto btnNext = Button("->", [&] {
        if(curMon + 1 > 12) {
            curMon = 1;
            curYear++;
        }else {
            curMon++;
        }

        monthContent = getMonthContent(curMon, curYear);
        holidaysContent = getHolidaysContent(curMon, curYear, holidaysReader);
    });

    auto btnPrev = Button("<-", [&] {
        if(curMon - 1 < 1) {
            curMon = 12;
            curYear--;
        }else {
            curMon--;
        }

        monthContent = getMonthContent(curMon, curYear);
        holidaysContent = getHolidaysContent(curMon, curYear, holidaysReader);
    });

    auto btnDelete = Button("Удалить", [&]{
        if(!regex_match(delDate, regex("[0-9]{1,2}"))){
            delError = "Введите корректное число!";
            return;
        }
        FileHandler delHandler("holidays.txt", FileHandler::IN_OUT_MODE);
        delHandler.deleteHoliday(stoi(delDate), curMon, curYear);
        delHandler.close();
        monthContent = getMonthContent(curMon, curYear);
        holidaysContent = getHolidaysContent(curMon, curYear, holidaysReader);
    });

    auto inputComponent = Container::Vertical({
        dateInput, holidaysInput, btnAdd, delDateInput, btnDelete
    });

    auto buttons = Container::Horizontal({btnPrev, btnNext});

    auto layout = Container::Vertical({buttons, inputComponent});

    auto component = Renderer(layout,
                              [&monthContent, &buttons, &dateInput,
                               &holidaysInput, &btnAdd, &error,
                               &holidaysContent, &delDateInput,
                               &btnDelete, &delError]{
        return vbox({
                hbox({
                    vbox(monthContent),
                    separator(),
                    buttons->Render(),
                }),
                separator(),
                text(error),
                dateInput->Render(),
                holidaysInput->Render(),
                btnAdd->Render(),
                text(delError),
                delDateInput->Render(),
                btnDelete->Render(),
                text("Праздники:"),
                vbox(holidaysContent) | border
                }) | border;
            });

    auto screen = ScreenInteractive::FitComponent();
    screen.Loop(component);
}

int main() {
    mainUI();
    return 0;
}
