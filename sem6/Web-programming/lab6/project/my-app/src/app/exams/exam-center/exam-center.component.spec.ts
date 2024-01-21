import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ExamCenterComponent } from './exam-center.component';

describe('ExamCenterComponent', () => {
  let component: ExamCenterComponent;
  let fixture: ComponentFixture<ExamCenterComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ExamCenterComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ExamCenterComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
