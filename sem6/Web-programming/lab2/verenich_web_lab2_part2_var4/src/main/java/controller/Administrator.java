package controller;

public class Administrator {

    public String name; // Имя администратора (менеджера университета)

    public Administrator(String l_name)
    {
        name = l_name;
    }

    public String getStartMessage()
    {
        return "Hello, my name is " + name + ".";
    }

    public String getChoiceMessage()
    {
        return """
                Enter the number of query you need to make:
                "1" - Select all abiturients of faculty
                "2" - Select all subjects
                "3" - Get abiturients of faculty with average mark more than average of faculty
                "4" - Change the result of abiturient in list
                "5" - Add new result of entrance exams.
                Or enter "exit" to exit the university""";
    }

    public String getMistakeMessage()
    {
        return "Your answer is incorrect. Please, try again.";
    }

    public String getExitMessage()
    {
        return "Thanks for visiting our university, goodbye!";
    }
}
