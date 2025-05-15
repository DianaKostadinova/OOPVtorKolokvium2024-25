#include <iostream>
#include <fstream>
using namespace std;
class NoProductFoundException {
    string category;
public:
    NoProductFoundException(const string& category) {
        this->category=category;
    }
    void message() {
        cout<<"No products from category "<<category<<" were found in the store"<<endl;
    }
};
class Product {
    string name;
    string category;
    int price;
    int available;
public:
    Product(const string &name="", const string& category="", int price=0, int available=0) {
        this->name=name;
        this->category=category;
        this->price=price;
        this->available=available;
    }
    int totalPrice() const {
        return price*available;
    }
    friend ostream& operator<<(ostream& os, const Product& p) {
        os<<p.name<<" ("<<p.category<<") "<<p.available<<" x "<<p.price<<" = "<<p.totalPrice()<<endl;
return os;
    }

    string getCategory() {
        return category;
    }
};
class Store {
    Product* p;
    int kolichina;
public:
    Store() {
    kolichina = 0;
    p = nullptr;
}
    Store& operator+=(const Product& pr) {
        Product* temp=new Product[kolichina+1];
        for (int i=0; i<kolichina; i++) {
            temp[i]=p[i];
        }
        temp[kolichina++]=pr;
        delete[]p;
        p=temp;
        return *this;
    }
    friend ostream &operator<<(ostream &os, const Store&s) {
        for (int i=0; i<s.kolichina;i++) {
            os<<s.p[i];
        }
        return os;
    }
    Store fromCategory(string &cat) {
         Store s;
        int br=0;
        for (int i=0; i<kolichina; i++) {
            if (cat==p[i].getCategory()) {
                s+=p[i];
                br++;
            }
        }
        if (br==0) {
            throw NoProductFoundException(cat);
        }

        return s;
    }
    ~Store() {
        delete[]p;
    }
};
void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {

    wtf();


    Store s;
ifstream fin("input.txt");

    string category;
    string name;
    int price,available;
while (getline(fin, name)&&getline(fin,category)&&fin>>price>>available) {
    fin.ignore();
    Product p(name,category,price,available);
    s+=p;
}
    fin.close();
    ofstream fout1("output1.txt");
    fout1<<s;
    fout1.close();
    cin >> category;
    ofstream fout2("output2.txt");
try {
     Store filtered=s.fromCategory(category);
        fout2<<filtered;
}catch (NoProductFoundException& e) {
    e.message();
}
    fout2.close();
    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}