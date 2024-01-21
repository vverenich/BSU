class TLocalStorage {
    AddValue(Key, Value) {
	var serialObj = JSON.stringify(Value)
        localStorage.setItem(Key, serialObj)	
    }
	
    GetValue(Key) {
	return JSON.parse(localStorage.getItem(Key))	
    }
	
    DeleteValue(Key) {
	localStorage.removeItem(Key)
    }
	
    GetKeys() {
	for (var i = 0; i < localStorage.length; ++i) {
	        console.log(localStorage.getItem(i))
	}	
    }
}

var obj = new TLocalStorage();

// --------------- PAGE ROOT
let root = document.querySelector('.page');

// --------------- FACULTY TABLE
let faculties = [
    [1, 'FIR'],
    [2, 'FAMCS'],
    [3, 'BIO'],
    [4, 'FB'],
    [5, 'FJ']
]
let facultyHead = ['id', 'title'];
let facultyQuestion = "faculties";

// --------------- SUBJECT TABLE
let subjects = [
    [1, 'Русский язык'],
    [2, 'Математика'],
    [3, 'Биология'],
    [4, 'Физика'],
    [5, 'Информатика']
]
let subjectHead = ['id', 'title'];
let subjectQuestion = "subjects";

// --------------- ABITURIENT TABLE
let abiturients = [
    [1, 'Веренич', 'Владислав', 'Николаевич', 2],
    [2, 'Зарембовский', 'Никита', 'Алексеевич', 2],
    [3, 'Зубцов', 'Иван', 'Алексеевич', 2],
    [4, 'Савко', 'Сергей', 'Андреевич', 1],
    [5, 'Бельская', 'Василина', 'Дмитриевна', 1],
]
let abiturientHead = ['id', 'surname', 'first_name', 'middle_name', 'faculty_id'];
let abiturientQuestion = "abiturients";

// --------------- LIST TABLE
let list = [
    [1, 1, 1, 90],
    [1, 2, 2, 80],
    [1, 3, 1, 70],
    [1, 4, 2, 85],
    [1, 5, 1, 93],
    [1, 1, 2, 92],
    [1, 2, 1, 97],
    [1, 3, 2, 70]
]
let listHead = ['id', 'abiturient_id', 'subject_id', 'mark'];
let listQuestion = "list";








let getAbiturientsOfFacultyForm = [
    ['input', 'text', 40, 'faculty', 'facultyID', 'Faculty\'s ID'],
    ['button', 'button', 'OK', 'buttonID', 'getAbiturientsOfFaculty()']
]
let addNewAbiturientForm = [
    ['input', 'text', 40, 'abiturient_id', 'abiturientID', 'abiturient_id'],
    ['input', 'text', 40, 'surname', 'abiturientSurname', 'surname'],
    ['input', 'text', 40, 'first_name', 'abiturientFirstName', 'first name'],
    ['input', 'text', 40, 'middle_name', 'abiturientMiddleName', 'middle name'],
    ['input', 'text', 40, 'faculty_id', 'abiturientfacultyID', 'faculty id'],
    ['button', 'button', 'Add', 'buttonAddNewAbiturient', 'addNewAbiturient()'],
]
let addAbiturientResultForm = [
    ['input', 'text', 40, 'list_id', 'listID', 'list_id'],
    ['input', 'text', 40, 'abiturient_id', 'abiturientID', 'abiturient_id'],
    ['input', 'text', 40, 'subject_id', 'subjectID', 'subject_id'],
    ['input', 'text', 40, 'mark', 'mark', 'mark'],
    ['button', 'button', 'Add', 'buttonAddAbiturientResult', 'addAbiturientResult()'],
]







// --------------- MAIN PAGE EVENT
function showAllAbiturients(){
    window.open("showAllAbiturients.html");
    
    /*
    var serialObj = JSON.stringify(faculties)
    localStorage.setItem("faculties", serialObj)
    */
}

function showAllSubjects(){
    window.open("showAllSubjects.html");
    
    /*
    var serialObj = JSON.stringify(subjects)
    localStorage.setItem("subjects", serialObj)
    */
}

function showAllFaculties(){
    window.open("showAllFaculties.html");
    /*
    var serialObj = JSON.stringify(abiturients)
    localStorage.setItem("abiturients", serialObj)
    */
}

function showResultsOfAllAbiturients(){
    window.open("showResultsOfAllAbiturients.html");
    /*
    var serialObj = JSON.stringify(list)
    localStorage.setItem("list", serialObj)
    */
}0

function showAbiturientsOfFaculty(){
    window.open("showAbiturientsOfFaculty.html");
}

function addAbiturient(){
    window.open("addNewAbiturient.html");
}

function addNewAbiturientsResult(){
    window.open("addNewAbiturientsResult.html");
}


function updateArrays() {
    //var obj = new TLocalStorage()
    abiturients = obj.GetValue(abiturientQuestion);
    faculties = obj.GetValue(facultyQuestion);
    subjects = obj.GetValue(subjectQuestion);
    list = obj.GetValue(listQuestion);
}

// --------------- GENERATE TABLES
function generateTable(root, headerValue, tableHead, elementsArray){
        
    //updateArrays()
    //var elementsArray = JSON.parse(localStorage.getItem(str.toString()))


    var header = document.createElement('h3');
    header.innerHTML = headerValue;
    root.append(header);
    var tableTag = document.createElement('table');
    root.append(tableTag);
    var tableHeader = document.createElement('tr');
    var tableHeaderColumn;
    var row;
    tableTag.append(tableHeader);
    for(let i = 0; i < tableHead.length; i++){
        tableHeaderColumn = document.createElement('th');
        tableHeaderColumn.innerHTML = tableHead[i];
        tableHeader.append(tableHeaderColumn);
    }
    for(let i = 0; i < elementsArray.length; i++){
        row = document.createElement('tr');
        tableTag.append(row);
        for(let j = 0; j < elementsArray[i].length; j++){
            var elements = document.createElement('td');
            elements.innerHTML = elementsArray[i][j];
            row.append(elements);
        }
    }
}




// --------------- GENERATE FORMS
function generateForm(formArray){
    var form = document.querySelector('form');
    for(let i = 0; i < formArray.length; i++){
        if(formArray[i][0] == 'input'){
                let input = document.createElement(formArray[i][0]);
                input.setAttribute("type", formArray[i][1]);
                input.setAttribute("size", formArray[i][2]);
                input.setAttribute("name", formArray[i][3]);
                input.setAttribute("id", formArray[i][4]);
                input.setAttribute("placeholder", formArray[i][5])
                input.setAttribute("required", 'true')
                form.append(input);
        }
        else if(formArray[i][0] == 'button'){
                let button = document.createElement(formArray[i][0]);
                button.setAttribute("type", formArray[i][1]);
                button.setAttribute("id", formArray[i][3]);
                button.setAttribute("onclick", formArray[i][4]);
                button.innerHTML = formArray[i][2];
                form.append(button);
        }
    }
}


function getAbiturientsOfFaculty(){
    
    updateArrays();
    
    console.log(abiturients)
    console.log(faculties)
    console.log(subjects)
    console.log(list)

    let root = document.querySelector('.result');
    let input = document.getElementById('facultyID').value;
    
    if (!input) {
        alert("No faculty ID provided")
        return
    }
    
    let resAbiturients = [];
    for(let i = 0; i < abiturients.length; i++){
        if(abiturients[i][4] == input){
            resAbiturients.push(abiturients[i]);
        }
    }
    if(resAbiturients.length > 0){
        var string = "Faculty id: "  + input;
        generateTable(root, string, abiturientHead, resAbiturients);
    }
    else{
        alert("No abiturient of this faculty.")
    }
}



function addNewAbiturient(){

    updateArrays();

    let root = document.querySelector('.result');

    let abiturient_id = document.getElementById('abiturientID').value;
    let abiturient_surname = document.getElementById('abiturientSurname').value;
    let abiturient_firstName = document.getElementById('abiturientFirstName').value;
    let abiturient_middleName = document.getElementById('abiturientMiddleName').value;
    let abiturient_facultyID = document.getElementById('abiturientfacultyID').value;

   
    abiturients.push([abiturient_id, abiturient_surname, abiturient_firstName, abiturient_middleName, abiturient_facultyID]);
    
   
    //var serialObj = JSON.stringify(abiturients)
    //localStorage.setItem("abiturients", serialObj)
   
    //var obj = new TLocalStorage()
    obj.AddValue("abiturients", abiturients)
    
} 

function addAbiturientResult(){

    updateArrays();

    let root = document.querySelector('.result');

    let list_id = document.getElementById('listID').value;
    let abiturient_id = document.getElementById('abiturientID').value;
    let subject_id = document.getElementById('subjectID').value;
    let mark = document.getElementById('mark').value;
     
   
    list.push([list_id, abiturient_id, subject_id, mark]);
    
  
    
    //var obj = new TLocalStorage()
    obj.AddValue("list", list)
 
    
    
    //var serialObj = JSON.stringify(list)
    //localStorage.setItem("list", serialObj)
}


