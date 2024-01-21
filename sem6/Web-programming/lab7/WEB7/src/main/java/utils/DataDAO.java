package utils;

import bean.UserAccount;
import config.SecurityConfig;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
  
public class DataDAO {
    
	 private DataSource dataSource;

	 public DataDAO(DataSource theDataSource) {
		
		 dataSource = theDataSource;
	 }
   
     // Find a User by userName and password.
	 public UserAccount findUser(String theUsername, String thePassword) throws Exception {
			
		    UserAccount theUser = null;
			
			Connection myConn = null;
			PreparedStatement myStmt = null;
			ResultSet myRs = null;
					 
			try {	
								
				// get connection to database
				myConn = dataSource.getConnection();
								
				// create sql to get selected student
				String sql = "SELECT * FROM task WHERE username = ? AND password = ?";
				
				// create prepared statement
				myStmt = myConn.prepareStatement(sql);
				
				// set params
				myStmt.setString(1, theUsername);
				myStmt.setString(2, thePassword); 
				
				// execute statement
				myRs = myStmt.executeQuery();
							
				if (myRs.next()) {
					
					int id = myRs.getInt("id");
					String username = myRs.getString("username");
					String pass = myRs.getString("password");
					String gender = myRs.getString("gender");
					String role = myRs.getString("role");
					
					// use the userId during construction
					if (role.equals("ADMIN"))
						theUser = new UserAccount(id, username, pass, gender, 
								SecurityConfig.ROLE_USER, SecurityConfig.ROLE_ADMIN);
					else 
						theUser = new UserAccount(id, username, pass, gender, 
								SecurityConfig.ROLE_USER);
				}
							
				return theUser;
						
			} finally {
					
					close(myConn, myStmt, myRs);
			}
	 }
	 
		private void close(Connection myConn, Statement myStmt, ResultSet myRs) {

			try {
				
				if (myRs != null) {
					
					myRs.close();
				}
				
				if (myStmt != null) {
					
					myStmt.close();
				}
				
				if (myConn != null) {
					
					myConn.close();   // doesn't really close it ... just puts back in connection pool
				}                     // and makes it available for someone else to use
			} catch (Exception exc) {
				
				System.out.println(exc);
			}
		}
}
