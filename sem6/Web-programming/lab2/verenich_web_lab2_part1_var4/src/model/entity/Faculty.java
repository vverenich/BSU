package model.entity;


public class Faculty {
    private int faculty_id;
    private String title;

    public String getTitle(){
        return title;
    }
    public void setTitle(String name){
        this.title=name;
    }
    public int getFacultyID(){
        return faculty_id;
    }
    public void setFacultyID(int id){
        this.faculty_id=id;
    }

    public Faculty(int faculty_id, String title) {
        setFacultyID(faculty_id);
        setTitle(title);
    }
    @Override
    public String toString() {
        return "\n--- Faculty info ---\n" +
                "faculty ID: " + getFacultyID() + "\n" +
                "title: " + getTitle() + "\n";
    }
}
