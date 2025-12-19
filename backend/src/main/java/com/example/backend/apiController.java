package com.example.backend;

import java.util.List;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
//Dont need to import User and UserRepository as they are in the same package

/*
This class is the API controller and injects the UserRepository to handle HTTP requests related to users.
It has methods to get all the users and add a new user, and it uses teh
UserRepository to interact with the database, so it can perform operations like fetching all users and saving a new user.

It also uses teh table mapping defined in the User entity class to map the User objects to the corresponding database table.


This class works by using Spring Boot's REST controller capabilities to define endpoints for user-related operations.
It extends the functionality of the UserRepository by providing HTTP endpoints that clients can interact with.
It also uses the User.java entity class to map the data between the application and the database.
*/
@RestController
@RequestMapping("/api/users")
public class apiController {

  private final UserRepository userRepository;

  public apiController(UserRepository userRepository) {
    this.userRepository = userRepository;
  }

  @GetMapping
  public List<User> getUsers() {
    return userRepository.findAll();
  }

  @PostMapping
  public ResponseEntity<User> addUser(@RequestBody User user) {
    User saved = userRepository.save(user);
    return new ResponseEntity<>(saved, HttpStatus.CREATED);
  }
}