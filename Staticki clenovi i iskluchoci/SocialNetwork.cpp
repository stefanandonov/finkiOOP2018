#include<iostream>
#include<cstring>
using namespace std;

class InvalidPassword {
private:
  char error[50];
public:
  InvalidPassword(const char * er) {
    strcpy(error,er);
  }
  void message() {
    cout << error << endl;
  }
};

class InvalidEmail {
private:
  char error[50];
public:
  InvalidEmail(const char * er) {
    strcpy(error,er);
  }
  void message() {
    cout << error << endl;
  }
};

class MaximumSizeLimit {
private:
  int n;
public:
  MaximumSizeLimit(int num) {
    n = num;
  }

  void message() {
    cout << "You can't add more than " << n << " users." << endl;
  }
};

class User {
private:
  char username[30];
  char password[30];
  char email[30];
public:
  User(const char* _username="", const char * _password="", const char * _email="") {
    strcpy(username,_username);
    setPassword(_password);
    setEmail(_email);
  }

  void setPassword(const char * _password) {
    int upper = 0;
    int lower = 0;
    int number = 0;
    for (int i=0; i < strlen(_password); ++i) {
      if (isupper(_password[i]))
        upper++;
      else if (islower(_password[i]))
        lower++;
      else if (isdigit(_password[i]))
        number++;
    }
    if (!upper || !lower || !number)
      throw InvalidPassword("Password is too weak.");
    strcpy(password,_password);
  }

  void setEmail(const char * mail) {
    int contains = 0;
      for (int i=0; i < strlen(mail); ++i) {
      	if (mail[i] == '@')
            contains++;
      }
      if (contains != 1)
      throw InvalidEmail("Mail is not valid.");
    strcpy(email,mail);
  }

  virtual double popularity() = 0;
};

class FacebookUser : public User {
private:
  int friends;
  int likes;
  int comments;
public:
  FacebookUser(const char* _username="", const char * _password="", const char * _email="",
               const int fr = 0, const int l = 0, const int comm = 0) : User(_username,_password,_email) {
                 friends = fr;
                 likes = l;
                 comments = comm;
               }
  double popularity() {
    return friends + 0.1 * likes + 0.5 * comments;
  }
};

class TwitterUser : public User {
private:
  int followers;
  int tweets;
  static double TWEET_VALUE;
public:
  TwitterUser(const char* _username="", const char * _password="", const char * _email="",
               const int fl = 0, const int tw = 0) : User(_username,_password,_email) {
                 followers = fl;
                 tweets = tw;
               }
  double popularity() {
    return followers + tweets * TWEET_VALUE;
  }

};

double TwitterUser::TWEET_VALUE = 0.5;

class SocialNetwork {

private:
  static int MAXIMUM_SIZE;
  User ** users;
  int currentUsers;
public:
  SocialNetwork(){
    users = new User*[0];
    currentUsers = 0;
  }

  SocialNetwork& operator += (User * u) {
    if (currentUsers == MAXIMUM_SIZE)
      throw MaximumSizeLimit(MAXIMUM_SIZE);
    User ** tmp = new User*[currentUsers + 1];
    for (int i=0; i < currentUsers; ++i) {
      tmp[i] = users[i];
    }
    tmp[currentUsers++] = u;
    delete [] users;
    users = tmp;
    return *this;
  }

  static void changeMaximumSize(int number) {
    MAXIMUM_SIZE = number;
  }

  double avgPopularity() {
    double pop = 0;
    for (int i=0; i < currentUsers; ++i) {
      pop += users[i] -> popularity();
      //cout << users[i] -> popularity() << endl;
    }
    return pop / currentUsers;
  }

  ~SocialNetwork() {
    delete [] users;
  }

};

int SocialNetwork::MAXIMUM_SIZE = 5;

int main() {

  SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
      cin >> username;
      cin >> password;
      cin >> email;
      cin >> userType;
      if (userType == 1) {
        int friends;
        int likes;
        int comments;
        cin >> friends >> likes >> comments;
        try {
        User * u = new FacebookUser(username,password,email,friends,likes,comments);
        network += u;
      } catch(InvalidPassword & e) {
        e.message();
      }
      catch (InvalidEmail &e) {
        e.message();
      }
      catch(MaximumSizeLimit &e) {
        e.message();
      }
      }
      else {
        int followers;
        int tweets;
        cin >> followers >> tweets;
        try {
        User * u= new TwitterUser(username,password,email,followers,tweets);
        network += u;
      }catch(InvalidPassword & e) {
        e.message();
      }
      catch (InvalidEmail &e) {
        e.message();
      }
      catch(MaximumSizeLimit &e) {
        e.message();
      }
      }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;
    try {
    User * u= new TwitterUser(username,password,email,followers,tweets);
    network += u;
  }catch(InvalidPassword & e) {
    e.message();
  }
  catch (InvalidEmail &e) {
    e.message();
  }
  catch(MaximumSizeLimit &e) {
    e.message();
  }
    cout << network.avgPopularity();

}
