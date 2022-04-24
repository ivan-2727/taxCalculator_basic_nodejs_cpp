std::vector <int> prsum_usual = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
std::vector <int> prsum_leap = {31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

int weekday_by_prsum(std::vector <int> prsum, int year, int month, int day) {
    int shift = 0;
    if (year >= 2013) shift = year - 2013 + (year - 2013)/4;
    else shift = -(2013 - year) - (2016 - year)/4;
    if (month == 0) return ((day + shift) % 7);
    return ((prsum[month-1] + day + shift) % 7); 
}

class date_time {         

    public:
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second; 

        date_time() {}
        date_time(int y, int mo, int d, int h, int mi, int s) {
            year = y; month = mo; day = d;
            hour = h; minute = mi; second = s;
        }
     
        int weekday() {
            if (abs(year - 2012)%4 == 0) {
                return weekday_by_prsum(prsum_leap, year, month, day);
            }
            return weekday_by_prsum(prsum_usual, year, month, day);
        }

        lli timestamp() {
            //the beginning of 2013 is zero
            int new_days = day-1;
            if (month > 0) {
                if (abs(year - 2012)%4 == 0) new_days += prsum_leap[month-1];
                else new_days += prsum_usual[month-1]; 
            }
    
            int prev_days = 0;
            if (year >= 2013) prev_days = ((year - 2013)/4)*prsum_leap[11] + ((year - 2013) - (year - 2013)/4)*prsum_usual[11];
            else prev_days = -((2016-year)/4)*prsum_leap[11] - ((2013 - year) - (2016-year)/4)*prsum_usual[11];

            return (new_days+prev_days)*24*60*60 + hour*60*60 + minute*60 + second;
        
        }   
};

