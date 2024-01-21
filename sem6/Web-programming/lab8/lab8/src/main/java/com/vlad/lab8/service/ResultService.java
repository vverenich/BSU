package com.vlad.lab8.service;

import java.util.List;
import java.util.UUID;

import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.vlad.lab8.entity.Result;
import com.vlad.lab8.repository.ResultRepository;

import lombok.RequiredArgsConstructor;

@Service
@RequiredArgsConstructor
public class ResultService {
    private final ResultRepository resultRepository;

    public List<Result> findAll() {
        return resultRepository.findAll();
    }

    public Result findById(UUID id) {
        return resultRepository.findById(id)
            .orElseThrow();
    }

    @Transactional
    public Result save(Result result) {
        return resultRepository.save(result);
    }

    @Transactional
    public void deleteById(UUID id) {
        resultRepository.deleteById(id);
    }
}
