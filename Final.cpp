#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Person {
private:
     string condition;
     int n, sick_days;
     bool infected,inoculated,status;

public:
Person() {
     sick_days=0;
}

string status_string() {
     if (sick_days>0) {
         condition="is sick";
    }else if (sick_days==-1) {
         condition="is susceptible";
    } else if (sick_days==-1) {
         condition="is recovered and inoculated";
    }
      return condition;
 }

int update() {
     int count=0;
     if(sick_days>0) { 
        sick_days=sick_days-1;

     if (sick_days==0) {
         sick_days=-1;
     }
      return sick_days;
 }    
}

void infect(int n) {
      if (sick_days>-1) {
         sick_days=n;
      }
    }

void recovered() {
      sick_days=-1;
}

bool is_stable() {
    if (sick_days==-1) {
       status_string();
   }
 }
int sick() {
    return sick_days;
   }
};

class Population {
private:
     vector<Person> people;
     int num_people,inoculated,day,inter;
     float r;

public:
     Population(int e) {
         BuildPop(e);
     }

     int random_infection() {
         int count=0;
         for (int p=0;p<people.size();p++) {
         int patient_zero=0;
             patient_zero=(int) rand()%people.size();
             float val1=(float) rand()/(float) RAND_MAX;
             if((people.at(patient_zero).sick()!=-1 && (val1>0.90))) {
                 people.at(patient_zero).infect(5);
                 break;
             }
           }
         }

     int count_infected() {
         int count=0;
         for (int p=0; p<people.size(); p++) {
              if (people.at(p).sick()>0) {
                 count=count+1;
              }
          }
	 return count;
       } 
     int count_inoculated() {
         int count=0;
         for (int p=0;p<people.size();p++) {
             if (people.at(p).sick()==1) {
                count=count+1;
             }
            }
                return count;
          } 
     
     int interaction_neighbor() {
         for(int p=0;p<people.size();p++) {
             int deltaneg=p-1;
             int deltapos=p+1;

             if(people.at(p).sick()>0 && ((deltaneg)>0)) {
                if(people.at(deltaneg).sick()==0) {
                   float value = (float) rand()/(float) RAND_MAX;
                   if ((value < set_probability_of_transfer(0.95))) {
                        people.at(deltaneg).infect(5);
                   } 
                 }   
                }
             if (deltapos<people.size()) {
                 if(people.at(p).sick()>0 && people.at(deltapos).sick()==0) {
                    float value = (float) rand()/(float) RAND_MAX;
                    if ((value < set_probability_of_transfer(0.95))) {
                         people.at(deltapos).infect(5);
                 }       
               }
             }
           }
	}

     int pop_update() {
      for (int i=0;i<people.size();i++) {
           people.at(i).update();
         }
       }

     void BuildPop(int Pe) {
          Person random;
          vector<Person> peep(Pe);
          for (auto &p:people) {
               p=random;
          }
          people=peep;
        } 		     

      int set_probability_of_transfer(int prob) {
          return prob;
      }

      int random_interaction(int interactions) {
          int count=0;
          for(int p=0; p < people.size(); p++) {
             if(people.at(p).sick()>0) {
               for (int i=0; i< interactions;i++) {
                   int patient_one=0;
                   patient_one=(int) rand() % people.size();
                   float val1=(float) rand()/(float) RAND_MAX;
                   if((people.at(patient_one).sick()==0) && (val1>0.95)) {
                       people.at(patient_one).infect(5);
                 }
               }
             }
           }
         }
      
      int inoculation() {
      int count=0;
          for (int p=0;p<people.size();p++) {
               int recovered_zero=0;
                   recovered_zero=(int) rand() % people.size();
                   if ((float) rand() / (float) RAND_MAX<0.15) {
                        people.at(recovered_zero).recovered();
                 }
               }
             }
           };
	
const int e{40000};

int main() {
    int day=1;
     srand((unsigned)time(0));
     Population population(e);
     population.inoculation();
     population.set_probability_of_transfer(0.95);
     population.random_infection();
     cout<<"On day " << day<< ": people infected " << population.count_infected()<<endl;
     while(population.count_infected()>0) {
           day=day+1;
           population.pop_update();
           population.interaction_neighbor();
           population.random_interaction(10);
           if(population.count_infected()==0) {
              cout<<"On day "<< day<<": people infected " << population.count_infected()<<endl;
              break;
            }
           cout<<"On day " <<day<< ": people infected "<<population.count_infected()<<endl;
        }
           cout<<population.count_inoculated()<<" people are inoculated at the end" << endl;
      }



