package com.vlad.lab8.repository;

import java.util.UUID;

import org.springframework.data.jpa.repository.JpaRepository;

import com.vlad.lab8.entity.Result;

public interface ResultRepository extends JpaRepository<Result, UUID> {
    
}
