// CPP program to detects face in a video

// Include required header files from OpenCV directory
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <utility>
#include <vector>
#include <sstream>
#include "opencv2\objdetect.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

using namespace std;
using namespace cv;

// note: all individual user and book files are saved using their username or book ID

unordered_set<string> users;
unordered_set<string> books;
int lineInBookFile = 5;

// getting all user and book IDs and storing them in an unordered set
void getAllUsersAndBooks(){
    
    fstream accounts;
    accounts.open("accounts.txt");
    if (accounts.is_open()){
        string acc;
        while (getline(accounts, acc)){
            users.insert(acc);
        }
    }

    fstream b;
    b.open("books.txt");
    if (b.is_open()){
        string book;
        while (getline(b, book)){
            users.insert(book);
        }
    }
}

// checking if username and password are correct for login
bool login(string username_attempt, string password_attempt){

    string u, p;
        
    fstream check;
    check.open(username_attempt + ".txt");
    getline(check, u);
    getline(check, p);
    
    if (u == username_attempt && p == password_attempt){
        return true;
    } else {
        return false;
    }
}

// adds user to unordered set, accounts.txt and creates a user file which stores username and password
bool register_user(string new_user, string new_pass){
        
    if (users.insert(new_user).second == true){ 

        ofstream user_file(new_user + ".txt");
        user_file << new_user << endl;
        user_file << new_pass << endl;
        user_file.close();

        ofstream add_user("accounts.txt", ios_base::app| ios_base::out);
        add_user << new_user << endl;
        add_user.close();

        return true;
    }
   
    return false;
    
}

// gets book details: id, title, author name and number of copies
void getBookDetails(string book_id){
    fstream bookfile;
    bookfile.open(book_id + ".txt");

    string info;
    if (bookfile.is_open()){
        cout << "--------------------------------------" << endl;
        cout << "Book info:" << endl;
        int line = 1;
        while (getline(bookfile, info))
        {
            switch(line){
                case 1:
                    cout << "Book ID: " + info << endl;
                    break;
                case 2:
                    cout << "Book title: " + info << endl;
                    break;
                case 3:
                    cout << "Author's first name: " + info << endl;
                    break;
                case 4:
                    cout << "Author's last name: " + info << endl;
                    break;
                case 5:
                    cout << "Number of copies: " + info << endl;
                    break;
            }
            line++;
        }
        cout << "--------------------------------------" << endl;
    } else {
        system("cls");
        cout << "Error opening book file" << endl;
    }
}

// adds book to books.txt and unordered set, create file to store details about the book
bool addBook(string book_id, string title, string authorFirst, string authorLast, int copies){
    if (users.insert(book_id).second == true){ 

        ofstream new_book(book_id + ".txt");
        new_book << book_id << endl;
        new_book << title << endl;
        new_book << authorFirst << endl;
        new_book << authorLast << endl;
        new_book << copies << endl;
        new_book.close();

        ofstream add_Book("books.txt", ios_base::app| ios_base::out);
        add_Book << book_id << endl;
        add_Book.close();

        return true;
    } else {
        return false;
    }
}

// edits book's txt file
void editBook(string book_id){
    cout << "Enter 1 to edit book title" << endl;
    cout << "Enter 2 to edit author's first name" << endl;
    cout << "Enter 3 to edit author's last name" << endl;
    cout << "Enter 4 to edit number of copies" << endl;
    int choice;
    cin >> choice;

    vector<string> info;
    fstream bookfile(book_id + ".txt");
    if (bookfile.is_open())
    {
        string text;
        while (getline(bookfile, text))
        {
            info.push_back(text);
        }
        bookfile.close();
        string replace;
        switch (choice)
        {
        case 1:
            cout << "Enter book title: ";
            cin >> replace;
            info[1] = replace;
            break;
        case 2:
            cout << "Enter author's first name: ";
            cin >> replace;
            info[2] = replace;
            break;
        case 3:
            cout << "Enter author's last name: ";
            cin >> replace;
            info[3] = replace;
            break;
        case 4:
            cout << "Enter number of copies: ";
            cin >> replace;
            info[4] = replace;
            break;
        }
        ofstream bookfile(book_id + ".txt");

        for (int i = 0; i < lineInBookFile; i++)
        {
            bookfile << info[i] << endl;
        }
        bookfile.close();
        system("cls");
    } else {
        system("cls");
        cout << "Error opening book file" << endl;
    }
    
}

int menu() {
    cout << "--------------------------------------" << endl;
    cout << "Enter 1 to login" << endl;
    cout << "Enter 2 to register new user" << endl;
    cout << "Enter 0 to quit" << endl;
    cout << "--------------------------------------" << endl;
    int input;
    cin >> input;
    return input;
}

int bookMenu(){
    cout << "--------------------------------------" << endl;
    cout << "Enter 1 to add a new book" << endl;
    cout << "Enter 2 to view a book's details" << endl;
    cout << "Enter 3 to edit book details" << endl;
    cout << "Enter 0 to log out" << endl;
    cout << "--------------------------------------" << endl;
    int input;
    cin >> input;
    return input;
}

void userBookAction(int choice){
    system("cls");
    if (choice == 1)
    {
        string book_id, title, authorFirst, authorLast;
        int copies;
        cout << "Enter book id: ";
        cin >> book_id;
        cout << "Enter book title: ";
        cin >> title;
        cout << "Enter author's first name: ";
        cin >> authorFirst;
        cout << "Enter author's last name: ";
        cin >> authorLast;
        cout << "Enter number of copies: ";
        cin >> copies;
        bool added = addBook(book_id, title, authorFirst, authorLast, copies);
        if (added)
        {
            system("cls");
            cout << "Book added" << endl;
        } else {
            system("cls");
            cout << "This book ID is already taken" << endl;
        }
        
    } else if (choice == 2)
    {
        system("cls");
        string book_id;
        cout << "Enter book id: ";
        cin >> book_id;
        getBookDetails(book_id);
    } else if (choice == 3){
        system("cls");
        string book_id;
        cout << "Enter book id: ";
        cin >> book_id;
        editBook(book_id);
    }
}

void start(){
    bool quit = false;
    while (!quit){
        int input = menu();
        
        if (input == 0)
        {
            quit = true;

        } else if (input == 2)
        {
            string new_user, new_pass;
            cout << "Enter a username: ";
            cin >> new_user;
            cout << "Enter a password: ";
            cin >> new_pass;

            bool registered = register_user(new_user, new_pass);
            if (registered){
                system("cls");
                cout << "User successfully created" << endl;
            } else {
                system("cls");
                cout << new_user + " already exists. Please try again" << endl;
            }
            
        } else if (input == 1)
        {
            string username_attempt, password_attempt;

            cout << "Enter your username: ";
            cin >> username_attempt;
            cout << "Enter your password: ";
            cin >> password_attempt;

            if (login(username_attempt, password_attempt)) {
                system("cls");
                cout << "Welcome " + username_attempt << endl;
                bool logOut = false;
                while (!logOut){
                    int choice = bookMenu();
                    if (choice == 0)
                    {
                       logOut = true;
                       system("cls");
                    } else if (choice == 1 || choice == 2 || choice == 3) {
                        userBookAction(choice);
                    } else {
                        cout << "Invalid entry" << endl;
                    }
                }
            } else {
                system("cls");
                cout << "Wrong username or password. Please try again" << endl;
            }
        } else {
            cout << "Invalid entry" << endl;
        }
    }
}

// Function for Face Detection
vector<Rect> detect_face_rectangles(const Mat frame);
string cascadeName;

bool detector(Mat &image, CascadeClassifier &cascade, double scale, int &counter);

bool startDetect()
{
	// VideoCapture class for playing video for which faces to be detected
	VideoCapture cap;

	Mat frame;

    int counter = 0;

	// PreDefined trained XML classifiers with facial features
	CascadeClassifier cascade;
	double scale = 1;

	// Change path before execution
	cascade.load("C:/Users/minwo/OneDrive/Desktop/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");

	// Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video

	cap.open(0);

	if (cap.isOpened())
	{
		// Capture frames from video and detect faces
		cout << "Face Detection Started...." << endl;
		while (1)
		{
			cap >> frame;
			if (frame.empty())
				break;
			Mat flipped;
			flip(frame, flipped, 1);
			if (detector(flipped, cascade, scale, counter))
			{
				cap.release();
				return true;
			}

			char c = (char)waitKey(10);

			// Press q to exit from window
			if (c == 27 || c == 'q' || c == 'Q')
				break;
		}
	}
	else
		cout << "Could not Open Camera";
	return true;
}

bool detector(Mat &image, CascadeClassifier &cascade, double scale, int &counter)
{
	vector<Rect> faces;
	Mat gray, imgResize;

	cvtColor(image, gray, COLOR_BGR2GRAY); // Convert to Gray Scale
	double fx = 1 / (scale);

	// Resize the Grayscale Image
	resize(gray, imgResize, Size(), fx, fx, INTER_LINEAR);
	equalizeHist(imgResize, imgResize);

	// Detect faces of different sizes using cascade classifier
	cascade.detectMultiScale(imgResize, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(175, 175));

	// Draw rectangles around the faces
	for (size_t i = 0; i < faces.size(); i++)
	{
		Rect r = faces[i];
		Mat smallImgROI;
		// vector<Rect> nestedObjects;
		Point center;
		Scalar color = Scalar(255, 255, 0); // Color for Drawing tool
		// int radius;

		double aspect_ratio = (double)r.width / r.height;

		rectangle(image, Point(cvRound(r.x * scale), cvRound(r.y * scale)), Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)), color, 3, 8, 0);

		smallImgROI = imgResize(r);
	}

	// Show Processed Image with detected faces
	imshow("Face Detection", image);

    if (faces.size() > 0)
	{
        counter++;
        if (counter == 20){
            destroyWindow("Face Detection");
            return true;
        }
	}	
	return false;
}

int main(int argc, char const *argv[])
{
	cout << "Please prove you are human, look into the camera" << endl;
	if (startDetect()){
		getAllUsersAndBooks();
        cout << "Face Detected" << endl;
    	start();
	}
    return 0;
}


