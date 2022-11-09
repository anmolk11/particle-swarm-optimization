/*
 * Particle Swarm Optimization Algorithm using cpp
 *
 * author : Anmol Khandelwal
 * last update : Nov 10, 2022 3:05 AM
 *
*/

#include<bits/stdc++.h>
using namespace std;

fstream wrt;

double cost_func(double x){
    return 5 + 4*x - x*x; 
}

double random(int b1,int b2){
    return b1 + ((rand() + 0.0) / ( RAND_MAX / (b2-b1) ) ) ;
}

/*----------------------------------- All the constants ------------------------------------------*/

double gbest_cost = DBL_MIN; // Global best cost

double gbest; // Global best postion

double W = 0.70; //Intertia {i.e. weight given to current velocity}

double c1 = 0.20; // Cognitive parameter

double c2 = 0.60; // Social parameter

int b1 = -10,b2 = 10; // Bounds {i.e. x ∈ [b1,b2]}

/*-----------------------------------------------------------------------------*/

class Particle{
    private:
    int particle_id;
    double curr_pos;
    double velocity;
    double pbest; // personal best position
    double pbest_cost; // personal best cost

    public:

    Particle(double curr_position,double velocity,int particle_id){
        this->curr_pos = pbest = curr_position;
        this->velocity = velocity;
        this->particle_id = particle_id;
        pbest_cost = cost_func(curr_pos);
        if(gbest_cost < pbest_cost){
            gbest_cost = pbest_cost;
            gbest = pbest;
        }
    } 

    void update_velocity(){
        double r1 = random(0,1);
        double r2 = random(0,1);

        velocity = W * velocity + c1 * r1 * (pbest - curr_pos) + c2 * r2  * (gbest - curr_pos);
    } 
    void update_position(){

        wrt<<curr_pos<<' ';

        curr_pos = curr_pos + velocity;

        // To stop particles from going out of bounds
        if(curr_pos < b1) curr_pos = b1;
        if(curr_pos > b2) curr_pos = b2;

        double curr_cost = cost_func(curr_pos);

        // optimization part
        if(pbest_cost < curr_cost){
            pbest_cost = curr_cost;
            pbest = curr_pos;
        }
        if(gbest_cost < pbest_cost){
            gbest_cost = pbest_cost;
            gbest = curr_pos;
        }
    }

    void printState(){
        cout<<"\nParticle #"<<particle_id<<"\nPosition : "<<curr_pos<<' '<<" | Velocity : "<<velocity<<" | Personal best : "<<pbest_cost<<'\n';
    }
};


int main(){
    srand(time(0));
    wrt.open("particle_pos.txt",ios::out);

    int num_of_particles = 15,maxiter = 100;

    vector<Particle> Swarm;

    for(int i = 1;i <= num_of_particles;i++){
        double pos = random(b1,b2);
        double vel = random(-1,1);

        Particle p(pos,vel,i);

        Swarm.push_back(p); 
    }

    for(int iter = 1;iter <= maxiter;iter++){
        cout<<"Iteration : "<<iter<<"\n\n";
        for(auto &particle : Swarm){
            particle.update_velocity();
            particle.update_position();
            particle.printState();
        }
        cout<<"\nMax value of F(x) is : "<<gbest_cost<<" at x = "<<gbest<<'\n';
        cout<<"\n------------------------------------------------------------\n";
        wrt<<'\n';
    }

    cout<<"Final Solution : \n";
    cout<<"Max value of F(x) is : "<<gbest_cost<<" at x = "<<gbest<<'\n';
}