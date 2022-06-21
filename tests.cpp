#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "FileHandler.h"
#include "Month.h"

TEST_CASE("Correct write holidays to file"){
    FileHandler f("test.txt", FileHandler::OUT_REWRITE_MODE);
    f.putHolidayToFile(1,1,2002, "holiday");
    ifstream stream("test.txt");
    char s[100];
    stream.getline(s, 100);
    CHECK(string(s) == "01.01.2002 holiday");
    stream.close();
    f.close();
}

TEST_CASE("Correct read holiday from file"){
    ofstream str("test.txt");
    str << "04.04.2002 holiday";
    str.close();
    FileHandler f("test.txt", FileHandler::IN_MODE);
    vector<string> s = f.getHolidaysFromFile(4,2002,false);
    CHECK(s[0] == "04.04.2002 holiday");
}

TEST_CASE("Correct read many holidays from file"){
    ofstream str("test.txt");
    for(int i = 1; i < 31; i++) {
        str << (to_string(i) + ".04.2002 holiday") << endl;
    }
    str.close();
    FileHandler f("test.txt", FileHandler::IN_MODE);
    vector<string> s = f.getHolidaysFromFile(4,2002,false);
    for(int i = 0; i < 31-1; i++) {
        CHECK(s[i] == (to_string(i+1) + ".04.2002 holiday"));
    }
}

TEST_CASE("Correct write many holidays to file"){
    FileHandler f("test.txt", FileHandler::OUT_REWRITE_MODE);
    for(int i = 10; i < 31; i++) {
        f.putHolidayToFile(i, 1, 2002, "holiday");
    }
    ifstream stream("test.txt");
    for(int i = 10; i < 31; i++) {
        char s[100];
        stream.getline(s, 100);
        CHECK(string(s) == (to_string(i) + ".01.2002 holiday"));
    }
    stream.close();
    f.close();
}

TEST_CASE("Correct write and read different holidays from file"){
    string h[] = {"9 мая", "Новый год", "День всемирной независимости от 3 черепах!", "Holiday day", "день 9% milk"};
    FileHandler f("test.txt", FileHandler::OUT_REWRITE_MODE);
    for(int i = 0; i < 5; i++){
        f.putHolidayToFile(i, 1, 2022, h[i]);
    }
    f.close();
    FileHandler fi("test.txt", FileHandler::IN_MODE);
    auto s = fi.getHolidaysFromFile(1, 2022,false);
    for(int i = 0; i < s.size(); i++){
        CHECK("0" + to_string(i) + "." + "01.2022 " + h[i] == s[i]);
    }
    fi.close();
}

TEST_CASE("Correct get by month and year"){
    FileHandler f("test.txt", FileHandler::OUT_REWRITE_MODE);
    f.putHolidayToFile(10, 1, 2020, "holiday");
    f.putHolidayToFile(11, 1, 2020, "holiday1");
    f.putHolidayToFile(10, 1, 2020, "holiday2");
    f.putHolidayToFile(10, 3, 2020, "holiday3");
    f.putHolidayToFile(10, 1, 2021, "holiday4");
    f.putHolidayToFile(10, 7, 2023, "holiday5");
    f.close();
    FileHandler fi("test.txt", FileHandler::IN_MODE);
    auto s1 = fi.getHolidaysFromFile(1, 2020,false);
    auto s2 = fi.getHolidaysFromFile(3, 2020,false);
    auto s3 = fi.getHolidaysFromFile(1, 2021,false);
    auto s4 = fi.getHolidaysFromFile(7, 2023,false);
    CHECK("10.01.2020 holiday" == s1[0]);
    CHECK("11.01.2020 holiday1" == s1[1]);
    CHECK("10.01.2020 holiday2" == s1[2]);
    CHECK("10.03.2020 holiday3" == s2[0]);
    CHECK("10.01.2021 holiday4" == s3[0]);
    CHECK("10.07.2023 holiday5" == s4[0]);
    fi.close();
}

TEST_CASE("Correct amount of days in months"){
    int correctDays[] = {31,28,31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for(int i = 0; i < 12; i++){
        CHECK(correctDays[i] == Month(i+1, 2022).getAmountOfdays());
    }
}

TEST_CASE("Correct names of months"){
    string correctNames[] = {"Январь", "Февраль", "Март",
                             "Апрель", "Май", "Июнь",
                             "Июль", "Август", "Сентябрь",
                             "Октябрь", "Ноябрь", "Декабрь"};
    int year = 2022;
    for(int i = 0; i < 12; i++){
        CHECK(correctNames[i] + " " + to_string(year) == Month(i+1, year).getName());
    }
}
