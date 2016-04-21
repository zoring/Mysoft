#ifndef FINDFRIENDS_H
#define FINDFRIENDS_H
#include <QListWidget>
#include <QWidget>
#include <vector>
#include <string>
using namespace std;
namespace Ui {
class FindFriends;
}

class FindFriends : public QWidget
{
    Q_OBJECT

public:
    explicit FindFriends(QWidget *parent = 0);
    ~FindFriends();
    bool LoadFoundFriend(vector<string> FoundFriends);
private:
    Ui::FindFriends *ui;
    class FoundFriends :public QListWidget{
    public:
        FoundFriends(int friendsid=0,string friendname = "",QListWidget *parent = 0);
    private:
        int friendid;
        string friendname;
    };

};

#endif // FINDFRIENDS_H
