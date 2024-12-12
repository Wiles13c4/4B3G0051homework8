#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <map>

using namespace std;

class Record {
protected:
    string id;
    string name;

public:
    Record(const string& _id, const string& _name)
        : id(_id), name(_name) {}

    virtual void display() const = 0;

    string getId() const { return id; }
    string getName() const { return name; }
};

class Student : public Record {
public:
    Student(const string& _id, const string& _name)
        : Record(_id, _name) {}

    void display() const override {
        cout << "學生 - 學號: " << id << ", 姓名: " << name << endl;
    }
};

class Teacher : public Record {
public:
    Teacher(const string& _id, const string& _name)
        : Record(_id, _name) {}

    void display() const override {
        cout << "教師 - 工號: " << id << ", 姓名: " << name << endl;
    }
};

class Course : public Record {
private:
    string teacherId;

public:
    Course(const string& _id, const string& _name, const string& _teacherId)
        : Record(_id, _name), teacherId(_teacherId) {}

    void display() const override {
        cout << "課程 - 課號: " << id
            << ", 課程名稱: " << name
            << ", 教師工號: " << teacherId << endl;
    }

    string getTeacherId() const { return teacherId; }
};

class CourseSelection {
private:
    string studentId;
    string courseId;

public:
    CourseSelection(const string& _studentId, const string& _courseId)
        : studentId(_studentId), courseId(_courseId) {}

    string getStudentId() const { return studentId; }
    string getCourseId() const { return courseId; }
};

class CourseManagementSystem {
private:
    vector<Student> students;
    vector<Teacher> teachers;
    vector<Course> courses;
    vector<CourseSelection> selections;

public:
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void addTeacher(const Teacher& teacher) {
        teachers.push_back(teacher);
    }

    void addCourse(const Course& course) {
        courses.push_back(course);
    }

    void addCourseSelection(const CourseSelection& selection) {
        selections.push_back(selection);
    }

    void listAllStudents() const {
        cout << "=== 所有學生 ===" << endl;
        for (const auto& student : students) {
            student.display();
        }
    }

    void listAllTeachers() const {
        cout << "=== 所有教師 ===" << endl;
        for (const auto& teacher : teachers) {
            teacher.display();
        }
    }

    void listAllCourses() const {
        cout << "=== 所有課程 ===" << endl;
        for (const auto& course : courses) {
            course.display();
        }
    }

    void listCourseSelectionsByStudent() const {
        cout << "=== 依學生分類的選課紀錄 ===" << endl;

        map<string, vector<CourseSelection>> studentSelections;

        // 將選課紀錄按學生分類
        for (const auto& selection : selections) {
            studentSelections[selection.getStudentId()].push_back(selection);
        }

        // 遍歷每個學生的選課紀錄
        for (const auto& studentEntry : studentSelections) {
            // 找到對應的學生
            auto studentIt = find_if(students.begin(), students.end(),
                [&studentEntry](const Student& s) { return s.getId() == studentEntry.first; });

            if (studentIt != students.end()) {
                cout << "\n學生: " << studentIt->getId()
                    << " - " << studentIt->getName() << endl;

                // 顯示該生選課資訊
                for (const auto& selection : studentEntry.second) {
                    auto courseIt = find_if(courses.begin(), courses.end(),
                        [&selection](const Course& c) { return c.getId() == selection.getCourseId(); });

                    if (courseIt != courses.end()) {
                        courseIt->display();
                    }
                }
            }
        }
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n 學生選課管理系統 " << endl;
            cout << "1. 新增學生" << endl;
            cout << "2. 新增教師" << endl;
            cout << "3. 新增課程" << endl;
            cout << "4. 新增選課紀錄" << endl;
            cout << "5. 列出所有學生" << endl;
            cout << "6. 列出所有教師" << endl;
            cout << "7. 列出所有課程" << endl;
            cout << "8. 列出依學生分類的選課紀錄" << endl;
            cout << "0. 結束系統" << endl;
            cout << "請輸入選項: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                string id, name;
                cout << "輸入學生學號: ";
                cin >> id;
                cout << "輸入學生姓名: ";
                cin >> name;
                addStudent(Student(id, name));
                break;
            }
            case 2: {
                string id, name;
                cout << "輸入教師工號: ";
                cin >> id;
                cout << "輸入教師姓名: ";
                cin >> name;
                addTeacher(Teacher(id, name));
                break;
            }
            case 3: {
                string id, name, teacherId;
                cout << "輸入課程編號: ";
                cin >> id;
                cout << "輸入課程名稱: ";
                cin >> name;
                cout << "輸入授課教師工號: ";
                cin >> teacherId;
                addCourse(Course(id, name, teacherId));
                break;
            }
            case 4: {
                string studentId, courseId;
                cout << "輸入學生學號: ";
                cin >> studentId;
                cout << "輸入課程編號: ";
                cin >> courseId;
                addCourseSelection(CourseSelection(studentId, courseId));
                break;
            }
            case 5: listAllStudents(); break;
            case 6: listAllTeachers(); break;
            case 7: listAllCourses(); break;
            case 8: listCourseSelectionsByStudent(); break;
            case 0: cout << "系統結束。" << endl; break;
            default: cout << "無效的選項，請重新輸入。" << endl;
            }
        } while (choice != 0);
    }
};

int main() {
    CourseManagementSystem cms;
    cms.showMenu();
    return 0;
}