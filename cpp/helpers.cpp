#include "date_time.h"

struct Subject {
   std::string vehicle;
   std::vector <date_time> dates;
};

bool comp(date_time dateA, date_time dateB) {
    if (dateA.year != dateB.year)
        return dateA.year < dateB.year;
    if (dateA.month != dateB.month)
        return dateA.month < dateB.month;
    if (dateA.day != dateB.day)
        return dateA.day < dateB.day;
    if (dateA.hour != dateB.hour)
        return dateA.hour < dateB.hour;
    if (dateA.minute != dateB.minute)
        return dateA.minute < dateB.minute;
    if (dateA.second != dateB.second)
        return dateA.second < dateB.second;
    return true;
}

std::string removeHeaders(char *buffer, int buflen) {
   std::string result;
   bool ok = false; 
   for (int i = 4; i < buflen; i++) {
      std::string t;
      printf("%c", buffer[i]);
      for (int j = i-4; j <= i-1; j++) t+=buffer[j];
      if (t=="\r\n\r\n") ok = true;
      if (ok) result += buffer[i];
   }
   return result;
}

std::vector <std::string> split(std::string s, std::set <char> sep) {
   std::string cur;
   std::vector <std::string> result;
   forup(i,0,s.size()) {
      if (sep.find(s[i]) != sep.end()) {
         if (!cur.empty()) result.push_back(cur);
         cur.clear();
      }
      else {
         cur.push_back(s[i]); 
      }
   }
   if (!cur.empty() and (int)cur[0]!=0) result.push_back(cur);
   return result; 
}

Subject parseRequest(std::string req) {

   Subject subject;
   auto lines = split(req, {'\n'});
   subject.vehicle = lines[0];
   forup(i,1,lines.size()-1) {
      auto x = split(lines[i], {' ', '-', ':'});
      int y = std::stoi(x[0]);
      int mo = std::stoi(x[1]);
      int d = std::stoi(x[2]);
      int h = std::stoi(x[3]);
      int mi = std::stoi(x[4]);
      int s = std::stoi(x[5]);
      date_time date = date_time(y,mo,d,h,mi,s);
      subject.dates.push_back(date); 
   }

   return subject;
}

int max(int x, int y) {
   if (x>y) return x;
   return y;
}