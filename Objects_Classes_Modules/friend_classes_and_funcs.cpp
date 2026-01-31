/*
Friend classes and functions, along with use of friend classes for private constructors
*/

// note:
// friend declaration is not mutual or transitive or inherited

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// forward declarations
class myclass;
template <typename T>
class secondclass;
void get_class_secret(myclass);

template <typename T>
class secondclass {
  public:
    secondclass(T val) : val{val}{}
    static void get_myclass_secret(myclass obj);
    T val;
};

// friend functions able to access private fields
// can define these friend functions within the class too - like creating nonmember function
// this works because of ADL - argument dependent lookup - compiler can find func because we pass myclass as arg
class myclass{
  // can either do the class or just a member function of the class
  // can specify specfic friend template accepted or keep general 
  
  // template typename<T>
  // friend class secondclass;
  friend void secondclass<int>::get_myclass_secret(myclass);
  friend void get_class_secret(myclass obj);
  friend void get_double_secret(myclass obj){
    std::cout << "Double the secret field is " << 2 * obj.secret_field << "\n";
  }

  public:
    myclass(int sf) : secret_field{sf}{}

  private:
    int secret_field{42};
};

template <typename T>
void secondclass<T>::get_myclass_secret(myclass obj){
  std::cout << obj.secret_field << "\n";
}

void get_class_secret(myclass obj){
  std::cout << "The secret field of this class is "<< obj.secret_field << "\n";
}

// Private constructors

// Forward declaration
class Worker;

class Manager {
public:
  std::shared_ptr<Worker> HireWorker(const std::string& Name);
  void ListTeam() const;

private:
  std::vector<std::shared_ptr<Worker>> Team{};
};

class Worker {
private:
  // Only the Manager class can call this constructor
  Worker(const std::string& Name) : Name{Name} {}
  std::string Name{};

  friend class Manager;
};

// Implementation must come after Worker is fully defined
std::shared_ptr<Worker> Manager::HireWorker(const std::string& Name) {
  auto NewWorker{std::shared_ptr<Worker>{new Worker{Name}}};
  Team.push_back(NewWorker);
  return NewWorker;
}

void Manager::ListTeam() const {
  std::cout << "Current Team:\n";
  for(const auto& WorkerInstance : Team) {
    // Manager can also access private members
    std::cout << "- " << WorkerInstance->Name << '\n';
  }
}

int main(){
  myclass mc{15};
  get_class_secret(mc);
  get_double_secret(mc);

  secondclass b{42};
  b.get_myclass_secret(mc);

  Manager TheManager{};
  TheManager.HireWorker("Charlie");
  TheManager.HireWorker("Dana");
  TheManager.HireWorker("Brian");

  TheManager.ListTeam();
}