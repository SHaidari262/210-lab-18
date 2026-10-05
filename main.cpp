#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Review {
    double rating;
    string comment;
    Review* next;
};

class Movie {
private:
    string title;
    Review* head;

public:
    Movie(string t = "") {
        title = t;
        head = nullptr;
    }

Movie(const Movie& other) {
    title = other.title;
    head = nullptr;

    vector<Review*> reviews;
    Review* current = other.head;

    while (current != nullptr) {
        reviews.push_back(current);
        current = current->next;
    }

    for (int i = reviews.size() - 1; i >= 0; i--) {
        addReview(reviews[i]->rating, reviews[i]->comment);
    }
}
Movie& operator=(const Movie& other) {
    if (this != &other) {
        Review* current = head;

        while (current != nullptr) {
            Review* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
        title = other.title;

        vector<Review*> reviews;
        current = other.head;

        while (current != nullptr) {
            reviews.push_back(current);
            current = current->next;
        }

        for (int i = reviews.size() - 1; i >= 0; i--) {
            addReview(reviews[i]->rating, reviews[i]->comment);
        }
    }

    return *this;
}
    void addReview(double rating, string comment) {
        Review* newReview = new Review;

        newReview->rating = rating;
        newReview->comment = comment;
        newReview->next = head;

        head = newReview;
    }
void printReviews() const {
    cout << "Movie Title: " << title << endl;

    Review* current = head;
    double total = 0.0;
    int count = 0;

    while (current != nullptr) {
        count++;

        cout << "  > Review #" << count << ": "
             << fixed << setprecision(1)
             << current->rating << ": "
             << current->comment << endl;

        total += current->rating;
        current = current->next;
    }

    if (count > 0) {
        cout << "  > Average: "
             << fixed << setprecision(1)
             << total / count << endl;
    }

    cout << endl;
}
    ~Movie() {
        Review* current = head;

        while (current != nullptr) {
            Review* temp = current;
            current = current->next;
            delete temp;
        }
    }
};
int main() {
    srand(time(0));

    ifstream inputFile("input.txt");

    if (!inputFile) {
        cout << "Error opening input.txt" << endl;
        return 1;
    }
    vector<Movie> movies;

    movies.push_back(Movie("Lord of the Rings"));
    movies.push_back(Movie("The Godfather"));
    movies.push_back(Movie("Star Wars"));
    movies.push_back(Movie("Jurassic Park"));
     string comment;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (getline(inputFile, comment)) {
                double rating = (rand() % 41 + 10) / 10.0;
                movies[i].addReview(rating, comment);
            }
        }
    }   
      for (int i = 0; i < 4; i++) {
        movies[i].printReviews();
    }  
    return 0;
}