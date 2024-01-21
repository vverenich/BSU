import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { ExamsModule } from './exams/exams.module';
import { ExamFormComponent } from './exams/exam-form/exam-form.component';

@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    ExamsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
