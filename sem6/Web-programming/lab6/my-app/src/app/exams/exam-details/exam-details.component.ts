
import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { ExamService, Exam } from '../mock-exam-list';


@Component({
  selector: 'app-exam-details',
  templateUrl: './exam-details.component.html',
  styleUrls: ['./exam-details.component.css']
})
export class ExamDetailsComponent implements OnInit {
  exam: Exam;

  constructor(private route: ActivatedRoute,
              private examService: ExamService) { }

  ngOnInit(): void {
  	const idParam = this.route.snapshot.paramMap.get('id');
  	if (idParam !== null) {
    		const id = +idParam;
    		const foundExam = this.examService.exams.find(exam => exam.id === id);
    		if (foundExam) {
      		this.exam = foundExam;
      		// do something with the exam
    		} else {
      		// handle the case where no exam was found
    		}
  	}
  }
}
