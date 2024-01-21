package University;


public class Subject {
    private int subject_id;
    private String title;

    public String getTitle(){
        return title;
    }
    public void setTitle(String name){
        this.title=name;
    }
    public int getSubjectID(){
        return subject_id;
    }
    public void setSubjectID(int id){
        this.subject_id=id;
    }

    public Subject(int id, String title) {
        setSubjectID(id);
        setTitle(title);
    }
    @Override
    public String toString() {
        return "\n--- Subjetc info ---\n" +
                "subject ID: " + getSubjectID() + "\n" +
                "title: " + getTitle() + "\n";
    }
}
