#include <iostream>
#include <fstream>
#include<vector>
#include <string.h>
#include <limits>
using namespace std;

//PERSON START
class person
{
private:
    char* name;
    string egn;
    char* add;
public:
    person();
    person(string, string, string);
    void setValues();
    ~person();
    char* getAdd()
    {
        return add;
    }
    string getEgn()
    {
        return egn;
    }
    char* getName()
    {
        return name;
    }
    void setName(char * p_name)
    {
        name = p_name;

    }
    void setEgn(string p_egn)
    {
        egn=p_egn;

    }
    void setAddress(char * p_add)
    {
        add=p_add;

    }
};
person::person()
{
    string p_name, p_egn, p_add;
    int month, day;
    bool doOver = false;
    //проверява дали има цифри в стринга с името и потребителя, не може да излезне от цикъла докато не въведе валидно
    //име според избраните критерии
    do
    {
        cout<<"Enter name(use only characters): ";
        getline(cin,p_name);
        //критерии 1: в името няма цифри
        doOver = std::string::npos != p_name.find_first_of("0123456789");
    }
    while(doOver);
    //проверява дали има букви в стринга с ЕГН-то, не може да излезне от цикъла докато не въведе валидно
    //егн според избраните критерии
    do
    {
        do
        {
            cout<<"Enter egn(10 numbers(numbers 3 and 4 are the month you were born and 5 and 6 are the day)): ";
            getline(cin,p_egn);
            //критерии 1: в ЕГН-то няма букви
            doOver = std::string::npos != p_egn.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
        }
        while(doOver);
        doOver=true;
        //критерии 2: ЕГН-то има размер 10

        if(p_egn.size()==10)
        {
            try
            {
                //критерии 3: частта от ЕГН-то която съответства на месец и ден от месеца трябва да има
                //месец със стойност до 12 включително и ден със стойност до 31 включително

                month = stoi(p_egn.substr(2,2));
                day = stoi(p_egn.substr(4,2));
            }
            catch(const invalid_argument& a)
            {
                month = 0;
                day = 0;
            }
        }
        else
        {
            month = 0;
            day = 0;
        }
        if(month<13&&month>0&&day>0&&day<32)
        {
            doOver=false;
        }
    }
    while(doOver);
    //адреса няма критерии понеже адреса може да съдържа и цифри и букви
    cout<<"Enter address ";
    getline(cin,p_add);
    //преминаване от string в char*
    name = new char[p_name.length() + 1];
    strcpy(name, p_name.c_str());
    egn=p_egn;
    add = new char[p_add.length() + 1];
    strcpy(add, p_add.c_str());


}
//конструктора приема параметри от типа string за по-добра прегледност на функията която го извиква
person::person(string p_name, string p_egn, string p_add)
{
    name = new char[p_name.length() + 1];
    strcpy(name, p_name.c_str());
    egn=p_egn;
    add = new char[p_add.length() + 1];
    strcpy(add, p_add.c_str());
}
person::~person()
{
    delete name;
    delete add;
}
ostream & operator << (ostream &obj1, person &obj2)
{
    cout << "Person\n";
    cout << "Name = ";
    obj1 << obj2.getName() << "\n";
    cout << "Egn = ";
    obj1 << obj2.getEgn() << "\n";
    cout << "Address = ";
    obj1 << obj2.getAdd() << "\n";
    return obj1;
}
//PERSON END

//ADDRESS START

class address
{
private:
    char *adr[5];
public:
    address(){}
    address(char *p_adr[5]);
    ~address();
    //get метод
    char ** returnAll();
    //set метод
    void setAddress(char *p_adr[5]);
    //предефинира се operator[] за по-лесна достъпност
    char * operator[](int i);
    //позволява промяна на един от петте адреса
    void editData(int i, string s);
    //потребителя въвежда данни за адресите чрез конзолата
    void setData();

};
address::address(char *p_adr[5])
{
    for(int i = 0; i<5; i++)
    {
        adr[i]=p_adr[i];
    }
}
address::~address()
{
    delete adr;
}
char ** address::returnAll()
{
    return adr;
}
void address::setAddress(char *p_adr[5])
{
    for(int i = 0; i<5; i++)
    {
        adr[i]=p_adr[i];
    }
}
char * address::operator[](int i)

{
    if(returnAll()[i]!=NULL)
    {
        return returnAll()[i];
    }
    return "";
}
void address::editData(int i, string s)
{
    strcpy(adr[i],s.c_str());
}
void address::setData()
{
    string s;
    vector<string> addresses;
    cout<<"(Write 0 to exit after the first time) Add address "<<0<<":";
    getline(cin,s);
    addresses.push_back(s);
    for(int i = 1; i<5; i++)
    {
        cout<<"(Write 0 to exit after the first time) Add address "<<i<<":";
        getline(cin,s);
        if(s.compare("0")==0)
        {
            break;
        }

        addresses.push_back(s);
    }
    while(addresses.size()<5)
    {
        addresses.push_back("default");
    }
    char * c[5];
    for(int i = 0; i<addresses.size(); i++)
    {

        c[i] = const_cast<char*>(addresses[i].c_str());

    }
    setAddress(c);

}
ostream & operator << (ostream &obj1, address &obj2)
{
    cout << "Addresses\n";
    for(int i = 0; i<5; i++)
    {
        if(obj2[i]!=NULL)
        {
            obj1<<obj2[i]<<"\n";
        }

    }
}
//ADDRESS END

//FILEMANAGEMENT START

class fileManagement
{
private:
    fstream fio;
    vector<string>addresses;
    vector<string>name;
    vector<string>egn;
    vector<string>ad;
    string arr;
public:
    void getFileData(address&, vector<person>&);
    void setFileData(address&, vector<person>&);
};
//метод който взима данните от файла
void fileManagement::getFileData(address& add, vector<person>& p)
{
    fio.open("sample.txt", ios::app | ios::out | ios::in);

    int i = 0;

//while loop, който запазва адресите във вектор
    while (!fio.eof())
    {

        getline(fio, arr);
        if(arr=="Person")
        {
            break;
        }
        addresses.push_back(arr);

    }
    //while loop, който запазва лицата във вектор
    while (!fio.eof())
    {

        getline(fio, arr);
        name.push_back(arr);
        getline(fio, arr);
        egn.push_back(arr);
        getline(fio, arr);
        ad.push_back(arr);


    }
//запазване на данните от файла в локален обект с който може да работим в програмата(обект от типа address)

    while(addresses.size()<5)
    {
        cout<<"Address size: "<<addresses.size();
        addresses.push_back("default");
    }
    char *c[5];
    for(i = 0; i<5; i++)
    {
        c[i] = const_cast<char*>(addresses[i].c_str());

    }
    add.setAddress(c);

//запазване на данните от файла в локален обект с който може да работим в програмата(обект от типа vector<person>)

    i=0;
    while(i<name.size())
    {
        person u(name[i],egn[i],ad[i]);
        p.push_back(u);
        i++;
    }
    fio.close();
}
//метод който записва данните във файл след като потребителя излезне от потребителския интерфейс
void fileManagement::setFileData(address& add, vector<person>& p)
{
    fio.open("sample.txt", ios::trunc | ios::out | ios::in);
    fio.seekg(0, ios::beg);

    while (fio)
    {
        fio << add << endl;
        //използваме думата "Person" за да окажем на четящата функция къде започват обектите от типа person
        fio<<"Person"<<endl;
        for(person per:p)
        {
            fio << per.getName() << endl;
            fio << per.getEgn() << endl;
            fio << per.getAdd() << endl;
        }
        break;
    }
    fio.close();
}
//FILEMANAGEMENT END

//INDEPENDENT FUNCTIONS START
//функцията премахва празните редове, които могат да се получат при запис във файл, като копира данните от
//един файл в друг, премахва го, и преименува другия като първия.
void blank_line()
{
    ifstream fin("sample.txt");

    ofstream fout;
    fout.open("temp.txt", ios::out);

    string str;
    while(getline(fin,str))
    {
        //прави се проверка дали реда е празен и ако да се проверява следващия ред, и така до достигане на ред
        //който не е празен
        while (str.length()==0)
            getline(fin,str);
//файла се корумпира ако не се добави нов човек към вектора при всяко изпълняване на програмата,
//решение което открих, че работи е да създам нов човек, чиито име, ЕГН и адрес са зададени с "p", който после се
//изтрива от blank_line(). Не е идеално, но за друго не се сетих
        if(str.compare("p")!=0)
        {
            fout<<str<<endl;
        }
    }
    fout.close();
    fin.close();
    remove("sample.txt");
    rename("temp.txt", "sample.txt");
}
void searchForMatchingAddresses(address& add, const vector<person> & people)
{
    //всеки човек се сравнява със всеки адрес
    for(person p : people)
    {
        for(int i = 0; i<5; i++)
        {
            if(strcmp(add[i],p.getAdd())==0)
            {
                cout<<"Person whose address matches one of those in addresses:"<<endl;
                cout<<p<<endl;
            }
        }
    }
}
//всеки човек се сравнява с въведеното ЕГН
void searchAddressByEgn(const vector<person> & people, string egn)
{
    for(person p : people)
    {
        if(p.getEgn().compare(egn)==0)
        {
            cout<<"Address of person with this egn:"<<endl;
            cout<<p.getAdd()<<endl;
        }
    }
}
//INDEPENDENT FUNCTIONS END


int main()
{
    fileManagement fm;
    address add;
    vector<person> people;

    fm.getFileData(add, people);
    //прави се проверка дали обектите съдържащи данните от файла са инициализирани и ако не(при несъществуващ или
   //празен файл) те се инициализират от потребителя.
    if(strcmp(add[0],"")==0)
    {
        add.setData();
    }
    if(people.empty()==1)
    {
        people.push_back(person());
    }
    string buff;
    int n;
    while(true)
    {
        cout<<"How would you like to proceed?"<<endl<<"0.Leave the program"<<endl;
        cout<<"1.Get information on the people whose addresses matches one of those in in the address array"
            <<endl<<"2.Find people's addresses by using their egn"<<endl<<"3.Add a person to the database"<<endl<<
            "4. Edit addresses"<<endl;
        getline(cin, buff);
        //Опция за излизане от интерфейса
        if(buff.compare("0")==0)
        {
            break;
        }
        //Търсене на хора чиито адреси съответстват на някой от тези в масива с адреси
        if(buff.compare("1")==0)
        {
            searchForMatchingAddresses(add, people);

        }
        //Търсене на адрес на човек по ЕГН-то му
        if(buff.compare("2")==0)
        {
            cout<<"Enter egn";
            getline(cin,buff);
            searchAddressByEgn(people,buff);

        }
        //Добавяне на нов човек към базата данни
        if(buff.compare("3")==0)
        {
            people.push_back(person());
        }
        //Дава право на потребителя да променя адресите в масива с адреси
        if(buff.compare("4")==0)
        {
            //принтира номера и името на адресите
            for(int i = 0; i<5; i++)
            {
                cout<<"Address number "<<i<<": "<<add[i]<<endl;
            }
            while(true)
            {
                cout<<"Choose which address you wish to add or change(pick number from 0 to 4): ";

                cin >> n;
                //проверка дали потребителя е въвел номер от 0 до 4
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
                    cout << "Bad entry.  Enter a NUMBER: ";
                    cin >> n;
                }
                if(n>-1&&n<5)
                {
                    break;
                }
            }
            cout<<"Write an address: ";
            //Първият getline() бива игнориран, затова добавих втори.
            getline(cin, buff);
            getline(cin, buff);
            add.editData(n,buff);
        }
    }


//файла се корумпира ако не се добави нов човек към вектора при всяко изпълняване на програмата,
//решение което открих, че работи е да създам нов човек, който после се
//изтрива от blank_line(). Не е идеално, но за друго не се сетих
    person p("p","p","p");
    people.push_back(p);
    //данните се запазват във файл
    fm.setFileData(add,people);
    //файлът се редактира за избягване на потенциални грешки при бъдещото му достъпване
    blank_line();
    return 0;
}
