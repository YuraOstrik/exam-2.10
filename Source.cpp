#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Participant {
protected:
    string name;
    int maxRun;
    int maxJump;
public:
    Participant(const string& name, int run, int jump) : name(name), maxRun(run), maxJump(jump) {}

    virtual void Run(int distance) {
        if (distance <= maxRun) {
            cout << name << " raced " << distance << " meters" << endl;
        }
        else {
            cout << name << " cannot do it ):" << endl;
        }
    }

    virtual void Jump(int height) {
        if (height <= maxJump) {
            cout << name << " jumped " << height << " meters" << endl;
        }
        else {
            cout << name << " oops " << endl;
        }
    }

    string getName() const {
        return name;
    }

    int getMaxRun() const {
        return maxRun;
    }

    int getMaxJump() const {
        return maxJump;
    }

    virtual ~Participant() {
        /*cout << "Dest---------" << endl;*/
    }
};

class Human : public Participant {
public:
    Human(const string& name) : Participant(name, 8000, 1) {}
};

class Cat : public Participant {
public:
    Cat(const string& name) : Participant(name, 5000, 5) {}
};

class Robot : public Participant {
public:
    Robot(const string& name) : Participant(name, 6000, 3) {}
};

class Obstacle {
public:
    virtual void Stop(Participant& participant) = 0;
    virtual ~Obstacle() {}
};

class RunTrack : public Obstacle {
    int length;
public:
    RunTrack(int length) : length(length) {}

    void Stop(Participant& participant) {
        cout << participant.getName() << " has started the distance (" << length << " meters)\n";
        participant.Run(length);
    }
};

class Wall : public Obstacle {
    int height;
public:
    Wall(int height) : height(height) {}

    void Stop(Participant& participant) {
        cout << participant.getName() << " tries to jump over a high wall " << height << " meters.\n";
        participant.Jump(height);
    }
};

int main() {
    vector<Participant*> participants = {
        new Human("Human"),
        new Cat("Cat"),
        new Robot("Robot")
    };

    vector<Obstacle*> obstacles = {
        new RunTrack(1500),
        new Wall(2),
        new RunTrack(5000),
        new Wall(3)
    };

    for (auto participant : participants) {
        cout << "\nParticipant: " << participant->getName() << "\n";

        for (auto obstacle : obstacles) {
            obstacle->Stop(*participant);

            if ((participant->getMaxRun() < 1500) || (participant->getMaxJump() < 2)) {
                cout << participant->getName() << " knocking out further attempts.\n";
                break;
            }
        }
    }

    for (auto participant : participants) {
        delete participant;
    }

    for (auto obstacle : obstacles) {
        delete obstacle;
    }

}



