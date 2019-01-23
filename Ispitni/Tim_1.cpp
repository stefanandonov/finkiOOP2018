#include<iostream>
#include<cstring>

using namespace std;


class FootballTeam {
    protected:
    char coach [50];
    int * goals;
    int number;
    static float coef;
    
    void copy (const FootballTeam &ft) {
        strcpy(this->coach,ft.coach);
        this->goals = new int [ft.number];
        this->number=ft.number;
        for (int i=0;i<ft.number;i++)
            this->goals[i]=ft.goals[i];
    }
    
    public:
    
    FootballTeam () {
        strcpy(coach,"");
        goals = new int [0];
        number=0;
    }
    
    FootballTeam(char * coach, int * goals, int number) {
        strcpy(this->coach,coach);
        this->goals = new int [number];
        this->number=number;
        for (int i=0;i<number;i++)
            this->goals[i]=goals[i];
    }
    
    FootballTeam (const FootballTeam &ft) {
        copy(ft);
    }
    
    FootballTeam &operator = (const FootballTeam &ft) {
        if (this!=&ft) {
            delete goals;
            copy(ft);
        }
        
        return *this;
    }
    
    
    ~FootballTeam () {
        delete goals;
    }
    
    static void setK (float k) {
        //cout<<"Coef changed from: "<<coef<<"to: "<<k<<endl;
        coef = k;
        
    }
    
    virtual float achievement () = 0;
    
    bool operator > (FootballTeam &t2) {
        return this->achievement() > t2.achievement();}
    
    char * getCoach () {
        return coach;
    }

   
    
}; 

float FootballTeam::coef = 2.0;



class Club : public FootballTeam {
    private:
    char name [50];
    int medals;
    
    public:
    Club () : FootballTeam() {
        
    }
    
    Club(char * coachName, int * goals, int no, char * name, int  medals) : FootballTeam(coachName,goals,no) {
        strcpy(this->name,name);
        this->medals = medals;
    }
    
    Club(const Club &c) {
        copy(c);
    }
    
    Club &operator = (const Club &c) {
        if (this!=&c) {
            delete goals;
            copy(c);
        }
        
        return *this;
    }  
    
    float achievement () {
        int sum = 0 ;
        for (int i=0;i<number;i++)
            sum+=goals[i];
        
        return sum*coef+medals;
    }
    
    Club& operator++() {
        ++medals;
        return *this;
    }
    
    friend ostream &operator << (ostream &out, const Club &c) {
        out<<"Coach: "<<c.coach<<", goals:";
        
        for (int i=0;i<c.number;i++)
           out<<" "<<c.goals[i];
        out<<", club name: "<<c.name<<", medals: "<<c.medals<<endl;
        return out;
    }

}; 

class NationalTeam : public FootballTeam {
    private:
    char country [50];
    int matches;
    
    public:
    NationalTeam () : FootballTeam() {
        
    }
    
    NationalTeam(char * coachName, int * goals, int no, char * country, int  matches) : FootballTeam(coachName,goals,no) {
        strcpy(this->country,country);
        this->matches = matches;
    }
    
    NationalTeam(const NationalTeam &c) {
        copy(c);
    }
    
    NationalTeam &operator = (const NationalTeam &c) {
        if (this!=&c) {
            delete goals;
            copy(c);
        }
        
        return *this;
    }  
    
    float achievement () {
        int sum = 0 ;
        for (int i=0;i<number;i++)
            sum+=goals[i];
        
        return sum*coef+matches;
    }
    
    NationalTeam& operator++() {
        ++matches;
        return *this;
    }
    
    friend ostream &operator << (ostream &out, const NationalTeam &c) {
        out<<"Coach: "<<c.coach<<", goals:";
        
        for (int i=0;i<c.number;i++)
           out<<" "<<c.goals[i];
        out<<", country name: "<<c.country<<", matches: "<<c.matches<<endl;
        return out;
    }

}; 

void greatestАchievement (FootballTeam ** teams, int n) {
    float max = -1.0;
    FootballTeam * maxTeam;
    for (int i=0;i<n;i++) {
        if (teams[i]->achievement()>max) {
            maxTeam=teams[i];
            max=teams[i]->achievement();
        }
    }
    
    cout<<maxTeam->getCoach()<<", Achievement: "<<maxTeam->achievement()<<endl;
}

void count (FootballTeam ** teams, int n) {
    int c = 0, t = 0;
    
    for (int i=0;i<n;i++) {
        Club * club = dynamic_cast<Club *> (teams[i]);
        if (club)
            c++;
        else
            t++;
    }
    
    cout<<"Clubs: "<<c<<", NationalTeams: "<<t<<endl;
    
}


int main() {
    int test_case_num;

    cin>>test_case_num;

    // for FootballTeam
    char coachName[50];
    int goals[100];
    int no;

    // for Club
    char name[50];
    int medals;

    // for NationalTeam
    char country[50];
    int matches;

    if (test_case_num == 1){
        cout<<"Testing the class Club and operator<< for Club"<<endl;
        cin.get();
        cin.getline(coachName,50);
        cin>>no;
        for(int i = 0; i < no; i++){
            cin>>goals[i];
        }

        cin.get();
        cin.getline(name,50);
        cin>>medals;

        Club c(coachName, goals, no, name, medals);

        cout<<c;
    }
    else if (test_case_num == 2){
        cout<<"Testing the class NationalTeam and operator<< for NationalTeam"<<endl;
        cin.get();
        cin.getline(coachName,50);
        cin>>no;
        for(int i = 0; i < no; i++){
            cin>>goals[i];
        }

        cin.get();
        cin.getline(country,50);
        cin>>matches;

        NationalTeam r(coachName, goals, no, country, matches);

        cout<<r;
    }
    else if (test_case_num == 3){
        cout<<"Testing the operator ++ for Club"<<endl;
        cin.get();
        cin.getline(coachName,50);
        cin>>no;
        for(int i = 0; i < no; i++){
            cin>>goals[i];
        }

        cin.get();
        cin.getline(name,50);
        cin>>medals;

        Club c(coachName, goals, no, name, medals);
        cout<<c;
        ++c;
        cout<<c;
    }
    else if (test_case_num == 4){
        cout<<"Testing the operator ++ for NationalTeam"<<endl;
        cin.get();
        cin.getline(coachName,50);
        cin>>no;
        for(int i = 0; i < no; i++){
            cin>>goals[i];
        }

        cin.get();
        cin.getline(country,50);
        cin>>matches;

        NationalTeam r(coachName, goals, no, country, matches);
        cout<<r;
        ++r;
        cout<<r;
    }
    else if (test_case_num == 5){
        cout<<"Testing achievement for Club"<<endl;
        cin.get();
        cin.getline(coachName,50);
        cin>>no;
        for(int i = 0; i < no; i++){
            cin>>goals[i];
        }

        cin.get();
        cin.getline(name,50);
        cin>>medals;

        Club c(coachName, goals, no, name, medals);
        cout<<c.achievement()<<endl;
    }
    else if (test_case_num == 6){
        cout<<"Testing achievement for NationalTeam"<<endl;
        cin.get();
        cin.getline(coachName,50);
        cin>>no;
        for(int i = 0; i < no; i++){
            cin>>goals[i];
        }

        cin.get();
        cin.getline(country,50);
        cin>>matches;

        NationalTeam r(coachName, goals, no, country, matches);
        cout<<r.achievement();
    }
    else if (test_case_num == 7){
        cout<<"Testing achievement"<<endl;

        int numTeams, teamType;
        cin>>numTeams;

        FootballTeam** ft = new FootballTeam*[numTeams];

        for(int j = 0; j < numTeams; j++){

            cin>>teamType; // 1-Club, 2-NationalTeam
            if(teamType == 1){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(name,50);
                cin>>medals;

                ft[j] = new Club(coachName, goals, no, name, medals);
            }
            if(teamType == 2){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(country,50);
                cin>>matches;

                NationalTeam r(coachName, goals, no, country, matches);
                ft[j] = new NationalTeam (coachName, goals, no, country, matches);
            }
        }

        for(int j = 0; j < numTeams; j++){
            cout<<ft[j]->achievement()<<endl;
        }
        
        for(int i = 0; i < numTeams; i++)
            delete ft[i];
        delete[]ft;
    }
    else if (test_case_num == 8){
        cout<<"Testing achievement"<<endl;

        int numTeams, teamType;
        cin>>numTeams;

        float k;
        cin>>k;

        FootballTeam::setK(k);

        FootballTeam** ft = new FootballTeam*[numTeams];

        for(int j = 0; j < numTeams; j++){

            cin>>teamType; // 1-Club, 2-NationalTeam
            if(teamType == 1){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(name,50);
                cin>>medals;

                ft[j] = new Club(coachName, goals, no, name, medals);
            }
            if(teamType == 2){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(country,50);
                cin>>matches;

                NationalTeam r(coachName, goals, no, country, matches);
                ft[j] = new NationalTeam (coachName, goals, no, country, matches);
            }
        }

        for(int j = 0; j < numTeams; j++){
            cout<<ft[j]->achievement()<<endl;
        }
        for(int i = 0; i < numTeams; i++)
            delete ft[i];
        delete[]ft;
    }
    else if (test_case_num == 9){
        cout<<"Testing operator >"<<endl;

        int numTeams, teamType;
        cin>>numTeams;

        FootballTeam** ft = new FootballTeam*[numTeams];

        for(int j = 0; j < numTeams; j++){

            cin>>teamType; // 1-Club, 2-NationalTeam
            if(teamType == 1){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(name,50);
                cin>>medals;

                ft[j] = new Club(coachName, goals, no, name, medals);
            }
            if(teamType == 2){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(country,50);
                cin>>matches;

                NationalTeam r(coachName, goals, no, country, matches);
                ft[j] = new NationalTeam (coachName, goals, no, country, matches);
            }
        }

        for(int j = 0; j < numTeams; j++){
            for(int i = j + 1; i < numTeams; i++)
                if(*ft[j] > *ft[i])
                    cout<<"1"<<endl;
                else if(*ft[i] > *ft[j])
                    cout<<"2"<<endl;
                else cout<<"0"<<endl;
        }
        
        for(int i = 0; i < numTeams; i++)
            delete ft[i];
        delete[]ft;
    }
    else if (test_case_num == 10){
        cout<<"Testing greatestАchievement"<<endl;

        int numTeams, teamType;
        cin>>numTeams;

        FootballTeam** ft = new FootballTeam*[numTeams];

        for(int j = 0; j < numTeams; j++){

            cin>>teamType; // 1-Club, 2-NationalTeam
            if(teamType == 1){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(name,50);
                cin>>medals;

                ft[j] = new Club(coachName, goals, no, name, medals);
            }
            if(teamType == 2){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(country,50);
                cin>>matches;

                NationalTeam r(coachName, goals, no, country, matches);
                ft[j] = new NationalTeam (coachName, goals, no, country, matches);
            }
        }

        greatestАchievement(ft,numTeams);
        
        for(int i = 0; i < numTeams; i++)
            delete ft[i];
        delete[]ft;
    }
    else if (test_case_num == 11){
        cout<<"Testing count"<<endl;

        int numTeams, teamType;
        cin>>numTeams;

        FootballTeam** ft = new FootballTeam*[numTeams];

        for(int j = 0; j < numTeams; j++){

            cin>>teamType; // 1-Club, 2-NationalTeam
            if(teamType == 1){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(name,50);
                cin>>medals;

                ft[j] = new Club(coachName, goals, no, name, medals);
            }
            if(teamType == 2){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(country,50);
                cin>>matches;

                NationalTeam r(coachName, goals, no, country, matches);
                ft[j] = new NationalTeam (coachName, goals, no, country, matches);
            }
        }

        count(ft,numTeams);
        
        for(int i = 0; i < numTeams; i++)
            delete ft[i];
        delete[]ft;
    }
    else if (test_case_num == 12){
        cout<<"Test All"<<endl;

        int numTeams, teamType;
        cin>>numTeams;

        float k;
        cin>>k;

        FootballTeam::setK(k);

        FootballTeam** ft = new FootballTeam*[numTeams];

        for(int j = 0; j < numTeams; j++){

            cin>>teamType; // 1-Club, 2-NationalTeam
            if(teamType == 1){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(name,50);
                cin>>medals;

                ft[j] = new Club(coachName, goals, no, name, medals);
            }
            if(teamType == 2){
                cin.get();
                cin.getline(coachName,50);
                cin>>no;
                for(int i = 0; i < no; i++){
                    cin>>goals[i];
                }

                cin.get();
                cin.getline(country,50);
                cin>>matches;

                NationalTeam r(coachName, goals, no, country, matches);
                ft[j] = new NationalTeam (coachName, goals, no, country, matches);
            }
        }

        for(int j = 0; j < numTeams; j++){
            cout<<"Achievement: "<<ft[j]->achievement()<<endl;
        }
        greatestАchievement(ft,numTeams);
        count(ft,numTeams);
        
        for(int i = 0; i < numTeams; i++)
            delete ft[i];
        delete[]ft;
    }
}
