package com.example.backend;

import org.springframework.data.jpa.repository.JpaRepository;

/*
Allows something called CRUD operations (Create, Read, Update, Delete) on User entities in the database.
CRUD operations are basic operations you can perform on data in a database, like adding, removal, etc

This class extends JpaRepository, which is a part of Spring Data JPA. By extending JpaRepository,
 UserRepository inherits several methods for working with User persistence, including methods for
  saving, deleting, and finding User entities.

  JPA allows us to use Java objects to represent database tables, making it easier to work with databases in a more object-oriented way.
  

*/
public interface UserRepository extends JpaRepository<User, Integer> {
}
