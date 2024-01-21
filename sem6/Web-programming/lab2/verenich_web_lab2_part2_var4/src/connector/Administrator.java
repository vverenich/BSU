package connector;

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
                "2" - Select all abiturients witch average mark more than average mark in faculty
                "3" - Get average mark of abiturients of faculty
                "4" - Add new abiturient
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
