
    //time of the day in seconds 

    std::vector <std::vector<int> > time_zones = {
        {21600, 23340+59, 8},
        {23400, 25140+59, 13},
        {25200, 28740+59, 18},
        {28800, 30540+59, 13},
        {30600, 53940+59, 8},
        {54000, 55740+59, 13},
        {55800, 61140+59, 18},
        {61200, 64740+59, 13},
        {64800, 66540+59, 8},
        {66600, 21540+59, 0},
    };

    std::vector <std::string> free_vehicles = {
        "MOTORCYCLE",
        "TRACTOR",
        "EMERGENCY",
        "DIPLOMAT",
        "FOREIGN",
        "MILITARY" 
    };

    std::map <int, std::vector<std::vector<int> > > free_dates =
    {
    {2013, {
            {1},
            {},
            {28,29},
            {1,30},
            {1,8,9},
            {5,6,21},
            {-1},
            {},
            {},
            {},
            {1},
            {24,25,26,31}
        }
    }
    };


