#include "FileHandler.h"

bool equal(std::string first, std::string second){
    return std::equal(first.begin(), first.end(), second.begin(), second.end());
}

FileHandler::FileHandler(const string& filepath, int mode) {
    this->mode = mode;
    this->filepath = filepath;
    if (mode == 1) {
        this->file = ifstream(filepath);
    }
    else if(mode == 0){
        this->outFile = ofstream(filepath, std::ios_base::app);
    }else if(mode == 2){
        this->outFile = ofstream(filepath);
    }else if(mode == 3){
        this->outFile = ofstream(filepath, std::ios_base::app);
        this->file = ifstream(filepath);
    }
}

FileHandler::~FileHandler() {
    if (mode == 1) {
        this->file.close();
    }else {
        this->outFile.close();
    }
    if(mode == 3){
    }
}

void FileHandler::close(){
    if (mode == 1) {
        this->file.close();
    }else {
        this->outFile.close();
    }
    if(mode == 3){
    }
}

void FileHandler::putHolidayToFile(int date, int month, int year, const string& holiday) {
    if (!outFile.is_open()) {
        throw "File is not opened!";
    }
    regex r("[0-9]+");
    if(!regex_match(to_string(date), r) ||
       !regex_match(to_string(month), r) ||
       !regex_match(to_string(year), r)){

        throw "Дата должна быть числом!";
    }
    if(holiday.empty()){
        throw "Введите праздник!";
    }
    string s_date, s_month;
    if(date < 10){
        s_date = "0" + to_string(date);
    }else{
        s_date = to_string(date);
    }
    if(month < 10){
        s_month = "0" + to_string(month);
    }else{
        s_month = to_string(month);
    }
    outFile << s_date << "." << s_month << "." << year << " " << holiday << endl;
}

vector<string> FileHandler::getHolidaysFromFile(int month, int year, bool defolt){
    if (!file.is_open()) {
        throw "File is not opened!";
    }
    vector<string> holidays;
    if (defolt){
        switch (month) {
            case 1:
                holidays.push_back("01.01." + to_string(year) + " Новый год!");
                holidays.push_back("06.01." + to_string(year) + " Сочельник");
                holidays.push_back("14.01." + to_string(year) + " Старый новый год");
                holidays.push_back("25.01." + to_string(year) + " День студента");
                break;
            case 2:
                holidays.push_back("14.02." + to_string(year) + " День святого валентина");
                holidays.push_back("23.02." + to_string(year) + " День защитника отечества");
                break;
            case 3:
                holidays.push_back("01.03." + to_string(year) + " Всемирный день кошек");
                holidays.push_back("08.03." + to_string(year) + " Международный женский день");
                holidays.push_back("21.03." + to_string(year) + " День Земли");
                break;
            case 4:
                holidays.push_back("01.04." + to_string(year) + " День смеха");
                holidays.push_back("05.04." + to_string(year) + " День геолога");
                holidays.push_back("12.04." + to_string(year) + " Пасха");
                break;
            case 5:
                holidays.push_back("01.05." + to_string(year) + " Праздник весны и труда");
                holidays.push_back("07.05." + to_string(year) + " День радио");
                holidays.push_back("25.05." + to_string(year) + " День филолога");
                holidays.push_back("28.05." + to_string(year) + " День пограничника");
                break;
            case 6:
                holidays.push_back("01.06." + to_string(year) + " День защиты детей");
                holidays.push_back("12.06." + to_string(year) + " День независимости России");
                break;
            case 7:
                holidays.push_back("03.07." + to_string(year) + " День ГАИ");
                holidays.push_back("07.07." + to_string(year) + " Иван Купала");
                holidays.push_back("16.07." + to_string(year) + " День металлурга");
                break;
            case 8:
                holidays.push_back("01.08." + to_string(year) + " День инкассатора");
                holidays.push_back("08.08." + to_string(year) + " День рождения альпинизма");
                break;
            case 9:
                holidays.push_back("01.09." + to_string(year) + " День знаний");
                holidays.push_back("02.09." + to_string(year) + " День российской гвардии");
                holidays.push_back("27.09." + to_string(year) + " День туризма");
                break;
            case 10:
                holidays.push_back("01.10." + to_string(year) + " День музыки");
                holidays.push_back("05.10." + to_string(year) + " День учителя");
                break;
            case 11:
                holidays.push_back("04.11." + to_string(year) + " День народного единства");
                holidays.push_back("28.11." + to_string(year) + " День матери");
                break;
            case 12:
                holidays.push_back("10.12." + to_string(year) + " День прав человека");
                holidays.push_back("22.12." + to_string(year) + " День энергетика");
                break;
        }
    }
    file.clear();
    file.seekg(0L, std::ios_base::beg);
    while(!file.eof()){
        char s[500];
        file.getline(s, 500, '\n');
        if(!regex_match(string(s), regex("[0-9]+.[0-9]+.[0-9]+[\\D\\d]+")))
            continue;
        string smonth = "", syear = "";
        int i = 0;
        while(s[i] != '.'){
            i++;
        }
        i++;
        while(s[i] != '.'){
            smonth.push_back(s[i]);
            i++;
        }
        i++;
        while(s[i] != ' '){
            syear.push_back(s[i]);
            i++;
        }
        int _month = 0;
        int _year = 0;
        try {
            _month = stoi(smonth);
            _year = stoi(syear);
        }catch(exception e){
            continue;
        }
        if (month == _month && _year == year) {
            holidays.push_back(s);
        }
    }
    if(holidays.empty())
        holidays.push_back("Нет праздников");
    return holidays;
}

void FileHandler::deleteHoliday(int day, int month, int year) {
    file = ifstream (filepath);
    vector<string> ss = vector<string>();
    while(!file.eof()){
        char s[500];
        file.getline(s, 500, '\n');
        if(!regex_match(string(s), regex("[0-9]+.[0-9]+.[0-9]+[\\D\\d]+")))
            continue;
        string sday = "", smonth = "", syear = "";
        int i = 0;
        while(s[i] != '.'){
            sday.push_back(s[i]);
            i++;
        }
        i++;
        while(s[i] != '.'){
            smonth.push_back(s[i]);
            i++;
        }
        i++;
        while(s[i] != ' '){
            syear.push_back(s[i]);
            i++;
        }
        int _day = 0;
        int _month = 0;
        int _year = 0;
        try {
            _day = stoi(sday);
            _month = stoi(smonth);
            _year = stoi(syear);
        }catch(exception e){
            continue;
        }
        if(!(_day == day && _month == month && _year == year))
            ss.push_back(string(s));
    }
    file.close();
    outFile = ofstream(filepath);
    for(int i =0;  i < ss.size(); i++){
        outFile << ss[i] << endl;
    }
    outFile.close();
}
