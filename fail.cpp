#include <iostream>
#include <map>
using namespace std;

class MyDate {
public:
    MyDate() = default;
    ~MyDate() = default;
    
    MyDate(uint32_t year, uint32_t month, uint32_t Day) :
        _Year(year), _Month(month), _Day(Day) {
        init();
    }
    
    void init() {
        for (int i = 1; i <= 12; i++) {
            if (i % 2 == 1) {
                _month_day_mapper.insert(std::make_pair(i, 31));
            } else {
                _month_day_mapper.insert(std::make_pair(i, 30));
            }
        }
        
        if (_Year % 4 == 0 && _Year / 400 == 0) {
            _month_day_mapper.insert(std::make_pair(2, 29));
        } else {
            _month_day_mapper.insert(std::make_pair(2, 28));
        }
        _month_day_mapper.insert(std::make_pair(8, 31));
        _month_day_mapper.insert(std::make_pair(9, 30));
        _month_day_mapper.insert(std::make_pair(10, 31));
        _month_day_mapper.insert(std::make_pair(11, 30));
        _month_day_mapper.insert(std::make_pair(12, 31));
    }
    
    bool check_valid() {
        if (0 < _Day || _Day > 31) {
            return false;
        }
        
        if (0 < _Month || _Month > 12) {
            return false;
        }
        
        std::map<uint32_t, uint32_t>::iterator pos =
            _month_day_mapper.find(_Month);
        if (_Day > pos->second) {
            return false;
        }
        
        return true;
    }
    
    
    friend int32_t operator-(MyDate date1, MyDate date2) {
        return date1.sum_day() - date2.sum_day();
    }
    
    std::string ToString() {
        std::cout << "this.Year" << _Year 
                   << "this.Month" <<_Month
                    << "this.Day" <<_Day << std::endl;
    }
    
private:
    int32_t sum_day() {
        int32_t sum = 0;
        for (int i = 0; i < _Year; i++) {
            sum += 365;
            if (i % 4 == 0 && i / 400 == 0) {
                sum += 1;
            }
        }
        
        for (int i = 1; i < _Month; i++) {
             std::map<uint32_t, uint32_t>::iterator pos =
                _month_day_mapper.find(i);
            sum += pos->second;
        }
        
        sum += _Day;
        
        return sum;
    }
    
    uint32_t _Year;
    uint32_t _Month;
    uint32_t _Day;
    
    std::map<uint32_t, uint32_t> _month_day_mapper;
};

int main() {
    //int a;
    //cin >> a;
    std::cout << "diff" << MyDate(2020,10,22) - MyDate(2010,10,11) << std::endl;
    cout << "Hello World!" << endl;
}

