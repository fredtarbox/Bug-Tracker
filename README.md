# Bug-Tracker
Bug Tracker App with C++ and File Handling With User and Admin Rights and login functionalities.
Default admin username and password
Username:- admin
Password:- 12345678

With Fogbugz switching from free to monthly charge, thought a simple bug tracker could fill all needs.

Saved all Fogbugz bugs as Microsoft Word docs. Plan to import them either straight from Word or from a .txt file.

First step was to get abhixsmasher version to run on Visual Studio 2022. Left the .sln project in github in Visual Studio 2017 (I think). Added BugTracker-Abhix2022.sln for Visual Studio 2022. Then added some features and comments to make easier. 
One feature was to put the bug id number as a three digit number and to put it as the first three characters of the file name followed by a dash.

Separated ziped data into Data Folder and OutputExamples Folder. 
Set up to look like this:

    Bug-Tracker folder
        Data subfolder
            Admin.out
            Login.out
            Users.out
            001-FirstBug.txt
            ...(all other bugs)
            
        Bin subfolder
            BugTracker-Abhix.exe
            
        OutputExamples subfolder
            AddAUser.txt
            ChangeTheStatusOfTheBug.txt
            CheckLoginHistory.txt
            FileANewBug.txt
            GetReportOfTheBugs.txt
            Login.txt
            Louout.txt
        
 That is where it stands now.       
        
