package com.example.backend;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.Table;

//Model class for user so that it can be mapped effecitlvey to the database table
/*
It is essentially a large table formatted as a class where each column in the table is represented as a field in the class.
The @Entity annotation indicates that this class is a JPA entity, meaning it will be mapped to a DB table
The @table specific the name of the table in teh databse
THe #id and @column is to show teh fields of the table and how it is all stored
*/
@Entity
@Table(name = "users")
public class User {
  @Id
  @GeneratedValue(strategy = GenerationType.IDENTITY)
  private Integer id;

  @Column(nullable = false, unique = true)
  private String username;

  @Column(nullable = false)
  private Integer birthYear;

  @Column(nullable = false)
  private Integer zipCode;

  // Store as JSON/text or a separate join table later; keeping simple for now.
  private String friendsList;

  public User() {
  }

  public Integer getId() {
    return id;
  }

  public void setId(Integer id) {
    this.id = id;
  }

  public String getUsername() {
    return username;
  }

  public void setUsername(String username) {
    this.username = username;
  }

  public Integer getBirthYear() {
    return birthYear;
  }

  public void setBirthYear(Integer birthYear) {
    this.birthYear = birthYear;
  }

  public Integer getZipCode() {
    return zipCode;
  }

  public void setZipCode(Integer zipCode) {
    this.zipCode = zipCode;
  }

  public String getFriendsList() {
    return friendsList;
  }

  public void setFriendsList(String friendsList) {
    this.friendsList = friendsList;
  }
}
