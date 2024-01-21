package com.vlad.lab8.entity;

import java.util.UUID;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import lombok.Data;

@Entity
@Data
public class Result {
    @Id
    @GeneratedValue
    private UUID id;

    private String enrollee;
    private Integer mark;
    private String name;
}
