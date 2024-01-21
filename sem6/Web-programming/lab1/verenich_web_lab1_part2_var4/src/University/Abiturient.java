package University;


public class Abiturient {
    private int abiturient_id;
    private String first_name; 
    private String surname;
    private String middle_name;
    private int faculty_id;

    public int getAbiturientID(){
        return abiturient_id;
    }
    public void setAbiturientID(int id){
        this.abiturient_id=id;
    }
    public String getAbiturientFirstName(){
        return first_name;
    }
    public void setAbiturientFirstName(String name){
        this.first_name=name;
    }
    public String getAbiturientSurname(){
        return surname;
    }
    public void setAbiturientSurname(String name){
        this.surname=name;
    }
    public String getAbiturientMiddleName(){
        return middle_name;
    }
    public void setAbiturientMiddleName(String name){
        this.middle_name=name;
    }
    public int getFacultyID(){
        return faculty_id;
    }
    public void setFacultyID(int id){
        this.faculty_id=id;
    }

    public Abiturient(int abiturient_id, String first_name, String surname, String middle_name, int faculty_id) {
        setAbiturientID(abiturient_id);
        setAbiturientFirstName(first_name);
        setAbiturientSurname(surname);
        setAbiturientMiddleName(middle_name);
        setFacultyID(faculty_id);
    }
    @Override
    public String toString() {
        return "\n--- Abiturient info ---\n" +
                "abiturient ID: " + getAbiturientID() + "\n" +
                "first name: " + getAbiturientFirstName() + "\n" +
                "surname: " + getAbiturientSurname() + "\n" +
                "middle name: " + getAbiturientMiddleName() + "\n" +
                "faculty id: " + getFacultyID() + "\n";
    }
}
