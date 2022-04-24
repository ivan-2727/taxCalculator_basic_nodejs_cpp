#include "taxrules.cpp"

int get_toll_fee(date_time date, std::vector <std::vector <int> > time_zones) {

    int t = date.hour*3600 + date.minute*60 + date.second; 

    for (auto zone : time_zones) {
        if (zone[0] <= zone[1]) {
            if (t >= zone[0] and t <= zone[1])
                return zone[2]; 
        }
        else {
            if (t >= zone[0] or t <= zone[1]) 
                return zone[2]; 
        }
    }
    return 0;
}

int get_tax(Subject subject) {

    for (auto vehicle : free_vehicles) {
        if (subject.vehicle == vehicle) return 0; 
    }
    
    std::vector <date_time> dates;

    for(auto date : subject.dates) {
        bool free = false;
        for(auto day : free_dates[date.year][date.month-1]) {
            if (day == date.day or day == -1) free = true;
        }
        int weekday = date.weekday(); 
        if (weekday == 5 or weekday == 6) free = true;  
        if (!free) dates.push_back(date); 
    }

    sort(dates.begin(), dates.end(), comp);  

    //start of 60min interval
    int start_index = 0;
    int start_time = dates[0].timestamp();

    int start_day_time = start_time;
    int daily_fee = 0;

    int total_fee = 0;

    int interval_fee;

    forup(i, 0, dates.size()-1) {

        lli time = dates[i].timestamp(); 

        if (time - start_time > 3600) {
            interval_fee = 0;
            forup(j, start_index, i-1) {
                interval_fee = max(get_toll_fee(dates[j], time_zones), interval_fee);
            }
            if (daily_fee + interval_fee <= 60) {
                total_fee += interval_fee;
                daily_fee += interval_fee;
            }
            else {
                total_fee += 60 - daily_fee;
                daily_fee = 60;
            }  
            start_time = time;
            start_index = i;
        }
        if (time - start_day_time > 86400) {
            daily_fee = 0;
            start_day_time = time;
        }
    }
    
    interval_fee = 0;
    forup(j, start_index, dates.size()-1) {
        interval_fee = max(get_toll_fee(dates[j], time_zones), interval_fee);
    }
    if (daily_fee + interval_fee <= 60) {
        total_fee += interval_fee;
        daily_fee += interval_fee;
    }
    else {
        total_fee += 60 - daily_fee;
        daily_fee = 60;
    }
    return total_fee;
}
