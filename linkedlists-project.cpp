#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

class ItemNode {
public:
  string brand;
  string model;
  double price;
  ItemNode *next; // pointer to next node

  ItemNode(string br, string md, double pr, ItemNode *ptr = 0) {
    brand = br;
    model = md;
    price = pr;
    next = ptr;
  }
};

class ItemList {
private:
  ItemNode *head, *tail;
  

public:
  string filename;
  ItemList(string file) {
    filename=file;
    head = tail = 0;
    ifstream check(file.c_str());
    if (check.good()){
      return;
    }
    else{
      ofstream create;
      create.open(file.c_str());
      create.close();
    }
  }

  int isEmpty() {
    return head == 0;
  }

  void addToHead(string br, string md, double pr) {
    head = new ItemNode(br, md, pr, head);
    if (tail == 0)
      tail = head;
  }

  void addToTail(string br, string md, double pr) {
    if (tail == 0) {
      head = tail = new ItemNode(br, md, pr);
      ofstream myfile;
      myfile.open(filename.c_str());
      myfile << br << "," << md << "," << pr << "\n";
      myfile.close();
    } else {
      tail->next = new ItemNode(br, md, pr);
      tail = tail->next;
      ofstream myfile;
      myfile.open(filename.c_str(),ios::app);
      myfile << br << "," << md << "," << pr << "\n";
      myfile.close();
    }
  }

  void deleteFromHead() {
    ItemNode *tmp = head;
    if (head == tail)
      head = tail = 0;
    else
      head = head->next;
    delete tmp;
  }

  void deleteFromTail() {
    if (head == tail) {
      delete head;
      head = tail = 0;
    } else {
      ItemNode *tmp;
      for (tmp = head; tmp->next != tail; tmp = tmp->next)
        ;

      delete tail;
      tail = tmp;
      tail->next = 0;
    }
  }

  void deleteNode(string br, string md, double pr) {
    if (head != 0) {
      if (head == tail && ( br == head->brand && md == head->model && pr == head->price ) ) {
        delete head;
        head = tail = 0;
      } else if (br == head->brand && md == head->model && pr == head->price) {
        // deleteFromHead();
        ItemNode *tmp = head;
        head = head->next;
        delete tmp;
      } else {
        ItemNode *p, *tmp;
        for (p = head, tmp = head->next; (tmp != 0 && tmp->brand != br && tmp->model != md && tmp->price != pr);
             p = p->next, tmp = tmp->next)
          ;

        if (tmp != 0) {
          p->next = tmp->next;
          if (tmp == tail)
            tail = p;
          delete tmp;
        }
      }
    }
  }

  bool isInList(string br, string md, double pr) const { // can't change any member state
    ItemNode *tmp;
    for (tmp = head; tmp != 0 && tmp->brand != br && tmp->model != md && tmp->price != pr; tmp = tmp->next)
      ;
    return tmp != 0;
  }

  void printAll() const {
    ItemNode *p;
    for (p = head; p != 0; p = p->next) {
      cout << p->brand << "," << p->model << "," << p->price << endl;
    }
  }

  ~ItemList() {
    for (ItemNode *p; !isEmpty();) {
      p = head->next;
      delete head;
      head = p;
    }
  }
};

string *splitString(string str) {
  static string array[3];
  std::vector<std::string> strings;
   std::istringstream f(str);
   std::string s;
   int iterator = 0;
   while (std::getline(f, s, ',')) {
         array[iterator] = s;
         iterator++;
         strings.push_back(s);
   }
   return array;
}

double convertToDouble(string str) {
  double price = atof(str.c_str());
  return price;
}

ItemList *reCreateDb(string file) {
  ItemList *dB = new ItemList(file);

  //Reading File
  ifstream file1(dB->filename.c_str());
  string temp;
  int lineCount=0;
  while(getline(file1,temp)){
    ++lineCount;
    }

  ifstream file2(dB->filename.c_str());
  string lines[lineCount];
  int lineIterator = 0;
  string line;
  while(getline(file2, line)){
    lines[lineIterator] = line;
    lineIterator++;
  }

  //recreate database from the readed file lines
  for (int i = 0; i<lineCount;i++){
    string var = lines[i];
    string *splitted = splitString(var);
    dB->addToTail(splitted[0],splitted[1],convertToDouble(splitted[2]));
  }
  return dB;

}

int main() {
  string Mobile_phones = "Mobile_Phones.txt";
  string Headphones = "Headphones.txt";
  string Laptops = "Laptops.txt";
  string Power_banks = "Power_Banks.txt";
  string Chargers = "Chargers.txt";

  ItemList *mobiles = reCreateDb(Mobile_phones);

  mobiles->addToTail("LG","Stylus 2", 899.99);
  // mobiles->addToTail("Samsung","Galaxy S2",1200.99);
  mobiles->addToTail("OnePlus","3T",560.99);
 //  mobiles->addToTail("Blackberry","Z",14399.99);
  // mobiles->addToTail("Samsung","Note 2", 1226.99);
  mobiles->printAll();

  cout<<endl;


  ItemList *laptops = reCreateDb(Laptops);
  laptops->addToTail("HP","Pavilion",1235.999);
  laptops->addToTail("HP","Envy",1245.68);
  // laptops->addToTail("Lenovo","YOGA 300", 1244.98);
  // laptops->addToTail("Apple","Mack Book Pro",99999.99);
  laptops->printAll();


  return 0;
}
