package application;
	
import java.awt.Color;
import java.util.ArrayList;

import com.verenich.Builders.VladSaladBuilder;
import com.verenich.Entities.Broccoli;
import com.verenich.Entities.Cabbage;
import com.verenich.Entities.Cucumber;
import com.verenich.Entities.Garlic;
import com.verenich.Entities.Onion;
import com.verenich.Entities.Pumpkin;
import com.verenich.Entities.Shallot;
import com.verenich.Salads.Salad;
import com.verenich.Salads.VladSalad;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.scene.layout.HBox;


public class Main extends Application implements EventHandler<ActionEvent>{
	Button buttonAddIngredient;
	ComboBox<String> comboBox;
	Text textCurrentSalad;
	Text textSalads;
	Button buttonAddSalad;
	TextField textField;
	Text textFats;
	Text textCalories;
	Text textProteins;
	Text textCarbohydrates;
	
	ArrayList<VladSalad> salads;
	VladSaladBuilder saladBuilder;
	
	public static void main(String[] args) {
		launch(args);
	}
	
	public void start(Stage primaryStage) throws Exception {
		salads = new ArrayList<VladSalad>();
		saladBuilder = new VladSaladBuilder();
		
		primaryStage.setTitle("SaladMaker");
		
		buttonAddIngredient = new Button();
		buttonAddIngredient.setText("Add");
		buttonAddIngredient.setOnAction(this);
		
		ObservableList<String> langs = FXCollections.observableArrayList("Broccoli", "Cabbage", "Cucumber", "Garlic", "Pumpkin", "Onion", "Shallot");
		comboBox = new ComboBox<String>(langs);
		comboBox.setValue("Broccoli");
		
		HBox hboxAddIngredient = new HBox(comboBox, buttonAddIngredient);
		hboxAddIngredient.setSpacing(10);
		
		Label labelIngredients = new Label("Ingredients:");
		
		textCurrentSalad = new Text(10, 50, "");
		textCurrentSalad.setFont(new Font(10));
		ScrollPane spCurrentSalad = new ScrollPane();
		spCurrentSalad.setContent(textCurrentSalad);
		spCurrentSalad.setPrefSize(150, 100);
		
		Label labelCalories = new Label("Calories:");
		textCalories = new Text("");
		VBox vboxCalories = new VBox(5);
		vboxCalories.getChildren().addAll(labelCalories, textCalories);
		
		Label labelProteins = new Label("Proteins:");
		textProteins = new Text("");
		VBox vboxProteins= new VBox(5);
		vboxProteins.getChildren().addAll(labelProteins, textProteins);
		
		Label labelFats = new Label("Fats:");
		textFats = new Text("");
		VBox vboxFats = new VBox(5);
		vboxFats.getChildren().addAll(labelFats, textFats);
		
		Label labelCarbohydrates = new Label("Carbohydrates:");
		textCarbohydrates = new Text("");
		VBox vboxCarbohydrates = new VBox(5);
		vboxCarbohydrates.getChildren().addAll(labelCarbohydrates, textCarbohydrates);
		
		HBox hboxSaladInfo = new HBox(vboxCalories, vboxProteins, vboxFats, vboxCarbohydrates);
		hboxSaladInfo.setSpacing(10);
		
		buttonAddSalad = new Button();
		buttonAddSalad.setText("Make Salad");
		buttonAddSalad.setPrefSize(100, 20);
		buttonAddSalad.setOnAction(this);
		textField = new TextField();
		textField.setPrefSize(70, 20);
		
		HBox hboxAddSalad = new HBox(buttonAddSalad, textField);
		hboxAddSalad.setSpacing(10);
		
		Label labelSalads = new Label("Salads:");
		
		textSalads = new Text(10, 50, "");
		textSalads.setFont(new Font(10));
		ScrollPane spSalads = new ScrollPane();
		spSalads.setContent(textSalads);
		spSalads.setPrefSize(150, 100);
		
		VBox vbox = new VBox(10);
		vbox.getChildren().addAll(hboxAddIngredient,labelIngredients, spCurrentSalad, hboxSaladInfo, hboxAddSalad, labelSalads, spSalads);
	     
		StackPane layout = new StackPane();
		layout.getChildren().add(vbox);
		
		Scene scene = new Scene(layout, 350, 300);
		primaryStage.setScene(scene);
		primaryStage.show();
	}
	
	
	@Override
	public void handle(ActionEvent event) {
		if(event.getSource() == buttonAddIngredient) {
			if(comboBox.getValue() == "Broccoli") {
				saladBuilder.addBroccoli(new Broccoli(1, 2, 3, 4));
			}
			
			if(comboBox.getValue() == "Cabbage") {
				saladBuilder.addCabbage(new Cabbage(1, 2, 3, 4, new Color(255, 240, 90)));
			}
			
			if(comboBox.getValue() == "Garlic") {
				saladBuilder.addGarlic(new Garlic(1, 2, 3, 4, 10));
			}
			
			if(comboBox.getValue() == "Pumpkin") {
				saladBuilder.addPumpkin(new Pumpkin(1, 2, 3, 4, "Field"));
			}
			
			if(comboBox.getValue() == "Onion") {
				saladBuilder.addOnion(new Onion(1, 2, 3, 4, new Color(255, 240, 90)));
			}
			
			if(comboBox.getValue() == "Shallot") {
				saladBuilder.addShallot(new Shallot(1, 2, 3, 4, new Color(255, 240, 90)));
			}
			
			if(comboBox.getValue() == "Cucumber") {
				saladBuilder.addCucumber(new Cucumber(1, 2, 3, 4, 10));
			}
			
			updateIngredientList();
			updateSaladInfo();
		}
		
		if(event.getSource() == buttonAddSalad) {
			if(saladBuilder.getListOfVegetables().size() != 0 && textField.getText() != "") {
				// Getting the salad and setting the name
				VladSalad salad = saladBuilder.getSalad();
				salad.setName(textField.getText());
				
				// Resetting the builder
				saladBuilder.reset();
				
				
				
				salads.add(salad);
				
				updateIngredientList();
				updateSaladList();
				updateSaladInfo();
			}
		}
	}
	
	public void updateIngredientList() {
		String list = new String("");
		
		ArrayList<String> arrayList = saladBuilder.getListOfVegetables();
		
		for(int i = 0; i < arrayList.size(); ++i) {
			list = list.concat(arrayList.get(i));
			list = list.concat("\n");
		}
		
		textCurrentSalad.setText(list);
	}
	
	public void updateSaladList() {
		String list = new String("");
		
		for(int i = 0; i < salads.size(); ++i) {
			list = list.concat(salads.get(i).getName());
			list = list.concat("\n");
		}
		
		textSalads.setText(list);
	}
	
	public void updateSaladInfo() {
		VladSalad salad = saladBuilder.getSalad();
		textFats.setText(Double.toString(salad.getFats()));
		textCalories.setText(Double.toString(salad.getCalories()));
		textProteins.setText(Double.toString(salad.getProteins()));
		textCarbohydrates.setText(Double.toString(salad.getCarbohydrates()));
	}
	
}
