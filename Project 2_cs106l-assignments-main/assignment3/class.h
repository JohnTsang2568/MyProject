#ifndef CLASS_H
#define CLASS_H

#include <string>

class character {
private:
    std::string name;
    std::string lp;
    std::string pp;
    int cp;

public:
    
    character();  
    character(const std::string& name, const std::string& lp, const std::string& pp);

    
    void setName(const std::string& name);
    void setLp(const std::string& lp);
    void setPp(const std::string& pp);
    void setCp(int cp);  

    
    std::string getName() const;
    std::string getLp() const;
    std::string getPp() const;
    int getCp() const;
};

#endif