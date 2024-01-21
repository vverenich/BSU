
import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Observable } from 'rxjs';
import { Exam } from '../mock-exam-list';
import { ExamsService } from '../services/exams.service';


@Component({
  selector: 'app-exam-details',
  templateUrl: './exam-details.component.html',
  styleUrls: ['./exam-details.component.css']
})
export class ExamDetailsComponent implements OnInit {
  exam$?: Observable<Exam>;

  constructor(private route: ActivatedRoute,
              private examService: ExamsService) { }

  ngOnInit(): void {
  	const id = this.route.snapshot.paramMap.get('id');
    this.exam$ = this.examService.getExam(id);
    this.exam$.subscribe(exam => console.log(exam));
  }
}
