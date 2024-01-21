package com.vlad.lab8.controller;

import java.util.List;
import java.util.UUID;

import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.vlad.lab8.entity.Result;
import com.vlad.lab8.repository.ResultRepository;
import com.vlad.lab8.service.ResultService;

import lombok.RequiredArgsConstructor;

@RestController
@RequestMapping("results")
@RequiredArgsConstructor
// @CrossOrigin(origins = "http://localhost:4200")
public class ResultController {
    private final ResultService resultService;

    @GetMapping
    public List<Result> findAll() {
        return resultService.findAll();
    }

    @GetMapping("/{id}")
    public Result findById(@PathVariable UUID id) {
        return resultService.findById(id);
    }

    @PostMapping
    public Result save(@RequestBody Result result) {
        return resultService.save(result);
    }

    @DeleteMapping("/{id}")
    public void deleteById(@PathVariable UUID id) {
        resultService.deleteById(id);
    }
}
