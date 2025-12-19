package com.example.backend;

import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.jdbc.core.JdbcTemplate;

@Configuration
public class DbTest {
  @Bean
  CommandLineRunner readRow(JdbcTemplate jdbc) {
    return args -> {
      try {
        String username = jdbc.queryForObject(
            "SELECT username FROM users WHERE username = ? LIMIT 1",
            String.class,
            "alice");
        System.out.println("Found in DB: " + username);
      } catch (Exception e) {
        System.out.println("DB test: No user 'alice' found yet (database may be empty)");
      }
    };
  }
}
