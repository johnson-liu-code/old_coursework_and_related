#include <iostream>
#include <string>
using namespace std;


// **************************** Question 2 ****************************
// 2) Create all components of the class Person, including
//    a print_me() method
// ********************************************************************
class Person
{
	// Your content here
public:
    Person ()
    {
        this->first_name = "";
        this->last_name = "";
        this->age = 0;
        this->gender = "";
        this->role = "";
        this->hours_per_week = 0;
        this->pay_per_hour = 0;
        this->years_experience = 0;
    }

    Person (string first_name, string last_name, int age, string gender, string role, int hours_per_week, float pay_per_hour, int years_experience)
    {
        this->first_name = first_name;
        this->last_name = last_name;
        this->age = age;
        this->gender = gender;
        this->role = role;
        this->hours_per_week = hours_per_week;
        this->pay_per_hour = pay_per_hour;
        this->years_experience = years_experience;
    }

    void set_first_name (string first_name)
    {
        this->first_name = first_name;
    }
    void set_last_name (string last_name)
    {
        this->last_name = last_name;
    }
    void set_age (int age)
    {
        this->age = age;
    }
    void set_gender (string gender)
    {
        this->gender = gender;
    }
    void set_role (string role)
    {
        this->role = role;
    }
    void set_hours_per_week (int hours_per_week)
    {
        this->hours_per_week = hours_per_week;
    }
    void set_pay_per_hour (float pay_per_hour)
    {
        this->pay_per_hour = pay_per_hour;
    }
    void set_years_experience (int years_experience)
    {
        this->years_experience = years_experience;
    }

    string get_first_name ()
    {
        return this->first_name;
    }
    string get_last_name ()
    {
        return this->last_name;
    }
    int get_age ()
    {
        return this->age;
    }
    string get_gender ()
    {
        return this->gender;
    }
    string get_role ()
    {
        return this->role;
    }
    int get_hours_per_week ()
    {
        return this->hours_per_week;
    }
    float get_pay_per_hour ()
    {
        return this->pay_per_hour;
    }
    int get_years_experience ()
    {
        return this->years_experience;
    }

    void print_me ()
    {
        cout << endl << "---------------------------------------------" << endl;
        cout << "First name: " << this->first_name << endl;
        cout << "Last name: " << this->last_name << endl;
        cout << "Age: " << this->age << endl;
        cout << "Gender: " << this->gender << endl;
        cout << "Role: " << this->role << endl;
        cout << "Hours per week: " << this->hours_per_week << endl;
        cout << "Pay per hour: " << this->pay_per_hour << endl;
        cout << "Years experience: " << this->years_experience << endl;
    }

private:
    string first_name;
    string last_name;
    int age;
    string gender;
    string role;
    int hours_per_week;
    float pay_per_hour;
    int years_experience;
};

// **************************** Question 3 ****************************
// 3) Create all components of the class Restaurant, including
//    a print_me() method
// ********************************************************************
class Restaurant
{
public:
	// Your content here
    Restaurant ()
    {
        this->name = "";
        this->num_of_chefs = 0;
        this->num_of_waiters = 0;
        this->num_of_dish_washers = 0;
        this->num_of_tables = 0;
        this->minimum_wage = 0;
        this->max_wage = 0;
        this->specialty = "";
    }

    Restaurant (string name, int num_of_chefs, int num_of_waiters, int num_of_dish_washers, int num_of_tables, float minimum_wage, float max_wage, string specialty)
    {
        this->name = name;
        this->num_of_chefs = num_of_chefs;
        this->num_of_waiters = num_of_waiters;
        this->num_of_dish_washers = num_of_dish_washers;
        this->num_of_tables = num_of_tables;
        this->minimum_wage = minimum_wage;
        this->max_wage = max_wage;
        this->specialty = specialty;
        this->manager = new Person();
        this->owner = new Person();
        this->cashier = new Person();
    }

    void set_name (string name)
    {
        this->name = name;
    }
    string get_name ()
    {
        return this->name;
    }

    void set_num_of_chefs (int num_of_chefs)
    {
        this->num_of_chefs = num_of_chefs;
    }
    int get_num_of_chefs ()
    {
        return this->num_of_chefs;
    }

    void set_num_of_waiters (int num_of_waiters)
    {
        this->num_of_waiters = num_of_waiters;
    }
    int get_num_of_waiters ()
    {
        return this->num_of_waiters;
    }

    void set_num_of_dish_washers (int num_of_dish_washers)
    {
        this->num_of_dish_washers = num_of_dish_washers;
    }
    int get_num_of_dish_washers ()
    {
        return this->num_of_dish_washers;
    }

    void set_num_of_tables (int num_of_tables)
    {
        this->num_of_tables = num_of_tables;
    }
    int get_num_of_tables ()
    {
        return this->num_of_tables;
    }

    void set_minimum_wage (float minimum_wage)
    {
        this->minimum_wage = minimum_wage;
    }
    float get_minimum_wage ()
    {
        return this->minimum_wage;
    }

    void set_max_wage (float max_wage)
    {
        this->max_wage = max_wage;
    }
    float get_max_wage ()
    {
        return this->max_wage;
    }

    void set_specialty (string specialty)
    {
        this->specialty = specialty;
    }
    string get_specialty ()
    {
        return this->specialty;
    }

    void print_me ()
    {
        cout << endl << "---------------------------------------------" << endl;
        cout << "Name of restaurant: " << this->name << endl;
        cout << "Number of chefs: " << this->num_of_chefs << endl;
        cout << "Number of waiters: " << this->num_of_waiters << endl;
        cout << "Number of dish washers: " << this->num_of_dish_washers << endl;
        cout << "Number of tables: " << this->num_of_tables << endl;
        cout << "Minimum wage: " << this->minimum_wage << endl;
        cout << "Max wage: " << this->max_wage << endl;
        cout << "Restaurant specialty: " << this->specialty << endl;
    }

    ~Restaurant ()
    {
        cout << endl << "The destructor was called." << endl;
        delete this->manager;
        delete this->owner;
        delete this->cashier;
    }

private:
	// Your content here
	Person* manager;
	Person* owner;
	Person* cashier;

    string name;
    int num_of_chefs;
    int num_of_waiters;
    int num_of_dish_washers;
    int num_of_tables;
    float minimum_wage;
    float max_wage;
    string specialty;
};

// **************************** Question 6 ****************************
// 6) Your function here
// ********************************************************************


int main()
{

	// **************************** Question 1 ****************************
	// 1) Create 3 variables of type pointer related to a restaurant scenario
	//    Have your program print your values
	// ********************************************************************
	// Your Answer here

    Restaurant *restaurant_01 = new Restaurant("Zensen", 4, 4, 1, 16, 12, 30, "Sushi");
    restaurant_01->print_me();
    delete restaurant_01;

    Restaurant *restaurant_02 = new Restaurant("Pho Le", 6, 8, 3, 20, 12, 30, "Pho");
    restaurant_02->print_me();
    delete restaurant_02;

    Restaurant *restaurant_03 = new Restaurant("Dominos", 4, 4, 1, 0, 10, 20, "Pizza");
    restaurant_03->print_me();
    delete restaurant_03;

	// **************************** Question 4 ****************************
	// 4) Create an array with 5 statically allocated restaurants
	//    Have your program print your values (you will need a loop) using
	//    the print_me() method of the object.
	// ********************************************************************
	// Your Answer here
    Restaurant sta_restaurant_array[5];

    sta_restaurant_array[0] = Restaurant("Dave's Donuts", 2, 1, 1, 0, 9, 20, "Donuts");
    sta_restaurant_array[1] = Restaurant("Sally's Smoothies", 2, 1, 1, 0, 8, 18, "Smoothies");
    sta_restaurant_array[2] = Restaurant("Jim's Jumbalaya", 2, 1, 1, 6, 8, 20, "Jumbalaya");
    sta_restaurant_array[3] = Restaurant("Ben's Biscuits", 2, 1, 1, 0, 10, 16, "Bakery");
    sta_restaurant_array[4] = Restaurant("Chen's Chinese Food", 3, 3, 1, 12, 10, 18, "Chinese Food");

    for (int i = 0; i < 5; i++)
    {
        sta_restaurant_array[i].print_me();
    }

	// **************************** Question 5 ****************************
	// 5) Create an array with 5 dynamically allocated restaurants
	//    Have your program print your values (you will need a loop) using
	//    the print_me() method of the object.
	// ********************************************************************
	// Your Answer here

    Restaurant *dyn_restaurant_array[5];

    dyn_restaurant_array[0] = new Restaurant("Celina's Chicken", 3, 2, 1, 6, 6, 18, "Chicken");
    dyn_restaurant_array[1] = new Restaurant("Cinia's Cakes", 2, 1, 1, 0, 8, 16, "Bakery");
    dyn_restaurant_array[2] = new Restaurant("Mo's Memberberries", 1, 1, 1, 0, 8, 14, "Fruit");
    dyn_restaurant_array[3] = new Restaurant("Iliana's Ice Cream", 2, 1, 1, 2, 10, 16, "Ice Cream");
    dyn_restaurant_array[4] = new Restaurant("Fred's Frozen Yogurt", 2, 1, 1, 2, 8, 16, "Frozen Yogurt");

    for (int i = 0; i < 5; i++)
    {
        dyn_restaurant_array[i]->print_me();
        delete dyn_restaurant_array[i];
    }

	char exit;
	cin >> exit;
	return 0;
}
