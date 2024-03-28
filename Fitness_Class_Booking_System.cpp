#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Member 
{
public:
    string name;
    Member(string name) : name(name) {}
};

class Booking 
{
public:
    Member* member;
    bool confirmation;

    Booking(Member* member) : member(member), confirmation(false) {}

    void confirm_booking() {
        confirmation = true;
    }
};

class FitnessClass 
{
public:
    string name;
    int slots;
    string timeslot;
    vector<Booking*> bookings;

    FitnessClass(string name, int slots, string timeslot) : name(name), slots(slots), timeslot(timeslot) {}

    bool book_slot(Member* member) {
        if (bookings.size() < slots) {
            Booking* booking = new Booking(member);
            bookings.push_back(booking);
            return true;
        }
        else {
            return false;
        }
    }

    int available_slots() const 
    {
        return slots - bookings.size();
    }
};

void viewAvailableClasses(const vector<FitnessClass>& classes)
{
    cout << "\nAvailable classes:\n";
    for (int i = 0; i < classes.size(); i++) 
    {
        cout << i + 1 << ". " << classes[i].name << " at " << classes[i].timeslot << " (" << classes[i].available_slots() << " slots available)\n";
    }
}
void bookClass(vector<FitnessClass>& classes, vector<Member>& members)
{
    cout << "\nEnter the number of the member: \n";
    for (int i = 0; i < members.size(); i++) 
    {
		cout << i + 1 << ". " << members[i].name << "\n";
	}
	int memberChoice;
	cin >> memberChoice;
	cout << "\n classes:-\n";
    for (int i = 0; i < classes.size(); i++) 
    {
		cout << i + 1 << ". " << classes[i].name << " at " << classes[i].timeslot << " (" << classes[i].available_slots() << " slots available)\n";
	}
	cout << "Enter the number of the class you want to book: ";
	int classChoice;
	cin >> classChoice;

    if (classChoice > 0 && classChoice <= classes.size() && memberChoice > 0 && memberChoice <= members.size()) 
    {
        if (classes[classChoice - 1].book_slot(&members[memberChoice - 1])) 
        {
			cout << "Booking successful!\n";
		}
        else {
			cout << "Booking failed. No available slots.\n";
		}
	}
    else
    {
		cout << "Invalid choice.\n";
	}
}

void cancelClass(vector<FitnessClass>& classes, vector<Member>& members)
{
    cout << "Enter the number of the class you want to cancel: ";
    int classChoice;
    cin >> classChoice;
    if (classChoice > 0 && classChoice <= classes.size())
    {
        cout << "Enter the number of the member: \n";
        for (int i = 0; i < members.size(); i++)
        {
            cout << i + 1 << ". " << members[i].name << "\n";
        }
        int memberChoice;
        cin >> memberChoice;
        if (memberChoice > 0 && memberChoice <= members.size())
        {
            for (int i = 0; i < classes[classChoice - 1].bookings.size(); i++)
            {
                if (classes[classChoice - 1].bookings[i]->member->name == members[memberChoice - 1].name)
                {
                    classes[classChoice - 1].bookings.erase(classes[classChoice - 1].bookings.begin() + i);
                    cout << "Booking cancelled successfully.\n";
                    break;
                }
            }
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
    else
    {
        cout << "Invalid choice.\n";
    }
}

void viewAllBookings(const vector<FitnessClass>& classes) 
{
   
    cout << "All bookings:\n";
    for (int i = 0; i < classes.size(); i++)
    {
        cout << classes[i].name<<"  " << classes[i].timeslot << ":-\n";
        for (int j = 0; j < classes[i].bookings.size(); j++)
        {
            cout << j + 1 << "- " << classes[i].bookings[j]->member->name << "\n";
        }
    }
    

}

void addMember(vector<Member>& members)
{
    cout << "Enter the name of the member: ";
    string name;
    cin >> name;
    Member member(name);
    members.push_back(member);
    cout << "Member added successfully.\n";
}

void viewAllMembers(const vector<Member>& members)
{
    cout << "\nAll members:\n";
    for (int i = 0; i < members.size(); i++) {
        cout << i + 1 << ". " << members[i].name << "\n";
    }
}

int main() 
{
    vector<FitnessClass> classes = 
    {
        FitnessClass("Yoga", 10, "08:00"),
        FitnessClass("Pilates", 15, "10:00"),
        FitnessClass("Zumba", 25, "12:00"),
        FitnessClass("Yoga", 8, "14:00"),
        FitnessClass("Pilates", 12, "16:00"),
        FitnessClass("Zumba", 22, "18:00"),
        FitnessClass("Yoga", 20, "20:00")
    };
    vector<Member> members =
    { 
        Member("Sami"),
        Member("Furqan"),
        Member("Jhanzaib"),
        Member("Hamza")
    };

    while (true) {
        cout << "\n\n\n";
        cout << "**************************************** Fitness Class Booking System ****************************************\n";
        cout << "1. View available classes\n";
        cout << "2. Book a class\n";
        cout << "3. Cancel a class\n";
        cout << "4. View all bookings\n";
        cout << "5. Add member\n";
        cout << "6. View all members\n";
        cout << "7. Exit\n";
        cout << "*************************************************************************************************************\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) 
        {
        case 1:
            viewAvailableClasses(classes);
            break;
        case 2:
            bookClass(classes, members);
            break;
        case 3:
            cancelClass(classes, members);
            break;
        case 4:
            viewAllBookings(classes);
            break;
        case 5:
            addMember(members);
            break;
        case 6:
            viewAllMembers(members);
            break;
        case 7:
            cout << "\nThank you for using the Fitness Class Booking System. Goodbye!\n";
            return 0;
        default:
            cout << "\nInvalid choice. Please try again.\n";
            break;
        }
    }

    system("pause");
    return 0;
}
