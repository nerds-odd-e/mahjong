#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

class Configuration
{
    public:
        static Configuration& getInstance()
        {
            static Configuration instance;
            return instance;
        }
        
    Configuration() {}  
    Configuration(Configuration const&) = delete;
    void operator=(Configuration const&) = delete;


    int GetMaxHoldingCount()const{return max_holding_count_;}
    void SetMaxHoldingCount(int count){max_holding_count_ = count;}

    int GetMaxMeldCount()const {return max_holding_count_/3;}
    
    private:
        int max_holding_count_ = 13;
};

#endif