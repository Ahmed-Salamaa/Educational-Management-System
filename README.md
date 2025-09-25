# Educational Management System

A comprehensive C++ console-based educational management system that facilitates interaction between students and doctors through courses and assignments.

## 🌟 Features

### User Management
- **Secure Authentication**: SHA-256 password hashing for secure user authentication
- **Role-based Access**: Two user types - Doctors and Students with different permissions
- **User Registration**: Complete signup process with email validation
- **Profile Management**: Users can update their personal information (name, username, email, password)

### Course Management
- **Course Creation**: Doctors can create new courses with detailed information
- **Course Registration**: Students can register for available courses
- **Course Information**: Name, code, description, and credit hours
- **Multi-user Support**: Multiple doctors can teach and multiple students can enroll in the same course

### Assignment System
- **Assignment Creation**: Doctors can create assignments for their courses
- **Grading System**: Flexible grading with customizable point values (1-100)
- **Submission Tracking**: Students can submit answers and track their progress
- **Grade Management**: Doctors can review and grade student submissions

### Reporting & Analytics
- **Grade Reports**: Students can view their grades for individual courses
- **Assignment Overview**: View all assignments with submission status
- **Course Analytics**: Doctors can see all enrolled students and their performance
- **Progress Tracking**: Real-time tracking of assignment submissions and grades

### Data Saving Support
- **Persistent Data Storage**: The project supports saving user, course, and assignment data to files, ensuring information is retained between sessions.

## 🏗️ System Architecture

### Core Classes

#### User Class (Base Class)
- Manages user authentication and profile information
- Handles course enrollment and assignment tracking
- Provides common functionality for both user types

#### Doctor Class (Inherits from User)
- Course creation and management
- Assignment creation and grading
- Student performance monitoring
- Course content management

#### Student Class (Inherits from User)
- Course enrollment
- Assignment submission
- Grade viewing and tracking
- Progress monitoring

#### Course Class
- Course information management
- User enrollment handling
- Assignment management within courses
- Access control and permissions

#### Assignment Class
- Assignment content and grading criteria
- Student submission handling
- Grade tracking and management
- Answer storage and retrieval

#### Services Class
- Main application controller
- Menu system navigation
- User session management
- Application workflow coordination

## 🚀 System Workflow

### 1. Authentication Flow
```
Start → Login/Signup Menu → User Authentication → Main Menu
```

### 2. Doctor Workflow
```
Login → Main Menu → Course Management Options:
├── Create New Course
├── List All Courses
├── Edit Existing Courses
│   ├── Add Assignments
│   ├── Review Student Submissions
│   ├── Grade Assignments
│   └── Manage Course Details
├── View Enrolled Students
└── User Profile Management
```

### 3. Student Workflow
```
Login → Main Menu → Student Options:
├── Browse Available Courses
├── Register for Courses
├── Submit Assignments
├── View Grades and Progress
├── Generate Grade Reports
└── User Profile Management
```

## 🛠️ Technical Specifications

### Dependencies
- **C++ Standard Library**: Core functionality
- **PicoSHA2**: Secure password hashing
- **Regex**: Input validation (email, name formats)
- **STL Containers**: Maps, vectors, and sets for data management

### Data Structures
- **Hash Maps**: Fast user, course, and assignment lookups
- **Vector Arrays**: Dynamic storage for user names and menu options
- **Static Counters**: Unique ID generation for all entities

### Security Features
- **Password Hashing**: SHA-256 encryption for password storage
- **Input Validation**: Regex-based validation for emails and names
- **Access Control**: Role-based permissions for different operations
- **Session Management**: Secure user session handling

## 📋 Installation & Setup

### Prerequisites
- C++ compiler with C++11 or later support
- Git (for cloning the repository)

### Clone Repository
```bash
# Clone the repository from GitHub
git clone https://github.com/Ahmed-Salamaa/Educational-Management-System.git

# Navigate to the project directory
cd "Educational-Management-System"
```

### Compilation
```bash
# Navigate to project directory
cd "/home/ahmed_salama/Projects/Educational Management System"

# Compile the project
g++ -I. main.cpp src/*.cpp -o output/app

# Run the application
./output/app
```

### VS Code Setup
The project includes VS Code configuration with:
- Code Runner extension setup
- Custom build tasks
- C++ IntelliSense configuration

## 🎯 Usage Guide

### For Students
1. **Registration**: Create an account with student type (type 2)
2. **Course Enrollment**: Browse and register for available courses
3. **Assignment Submission**: Submit answers for course assignments
4. **Grade Tracking**: Monitor your progress and view grade reports

### For Doctors
1. **Registration**: Create an account with doctor type (type 1)
2. **Course Creation**: Set up new courses with detailed information
3. **Assignment Management**: Create assignments and manage grading
4. **Student Monitoring**: Review student submissions and provide grades

## 📊 System Capabilities

### Data Management
- **Persistent Sessions**: User data maintained during application runtime
- **Relationship Tracking**: Complex relationships between users, courses, and assignments
- **Dynamic Memory Management**: Efficient resource allocation and cleanup
- **Data Saving Support**: System saves data to files, allowing recovery of users, courses, and assignments after program restarts.

### Validation & Error Handling
- **Input Validation**: Comprehensive validation for all user inputs
- **Error Recovery**: Graceful handling of invalid operations
- **User Feedback**: Clear error messages and success confirmations

### Scalability Features
- **Unlimited Users**: Support for any number of students and doctors
- **Unlimited Courses**: No limit on course creation
- **Flexible Assignments**: Support for various assignment types and grading scales

## 🔧 Configuration

### File Structure
```
Educational Management System/
├── include/                 # Header files
│   ├── assignment.h
│   ├── course.h
│   ├── doctor.h
│   ├── help_fun.h
│   ├── picosha2.h
│   ├── servies.h
│   ├── student.h
│   └── user.h
├── src/                     # Source files
│   ├── assignment.cpp
│   ├── course.cpp
│   ├── doctor.cpp
│   ├── help_fun.cpp
│   ├── servies.cpp
│   ├── student.cpp
│   └── user.cpp
├── output/                  # Compiled executables
├── main.cpp                 # Main application entry point
└── README.md               # This file
```

## 🌐 Cross-Platform Support

The system is designed to work across different operating systems:
- **Windows**: Full compatibility with Windows systems
- **Linux**: Native Linux support
- **macOS**: Compatible with macOS environments

## 📈 Future Enhancements

Potential areas for expansion:
- **Database Integration**: Persistent data storage
- **Web Interface**: Browser-based access
- **Advanced Reporting**: Detailed analytics and insights
- **File Upload Support**: Document and media assignment submissions
- **Real-time Notifications**: Assignment due dates and grade updates

## 🤝 Contributing

This is an educational project designed to demonstrate object-oriented programming concepts and system design in C++.

## 📄 License

Educational use project - part of software development coursework.

---

**Note**: This system is designed for educational purposes and demonstrates key concepts in object-oriented programming, data structures, and system design using C++.
