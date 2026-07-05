/*
 * Library Management System
 * A console-based Java application for managing a library's book inventory.
 * Supports adding, viewing, searching, issuing, returning, and deleting books.
 * Book records are persisted to a local text file (library.txt).
 *
 * Compile: javac LibraryManagementSystem.java
 * Run:     java LibraryManagementSystem
 */

import java.io.*;
import java.util.*;

public class LibraryManagementSystem {

    static final String FILE_NAME = "library.txt";
    static List<Book> books = new ArrayList<>();
    static Scanner scanner = new Scanner(System.in);

    static class Book {
        int id;
        String title;
        String author;
        boolean issued;

        Book(int id, String title, String author, boolean issued) {
            this.id = id;
            this.title = title;
            this.author = author;
            this.issued = issued;
        }

        String toFileLine() {
            return id + "|" + title + "|" + author + "|" + issued;
        }

        static Book fromFileLine(String line) {
            String[] parts = line.split("\\|");
            return new Book(Integer.parseInt(parts[0]), parts[1], parts[2], Boolean.parseBoolean(parts[3]));
        }
    }

    public static void main(String[] args) {
        loadBooks();
        boolean running = true;

        while (running) {
            System.out.println("\n===== LIBRARY MANAGEMENT SYSTEM =====");
            System.out.println("1. Add Book");
            System.out.println("2. View All Books");
            System.out.println("3. Search Book by Title");
            System.out.println("4. Issue Book");
            System.out.println("5. Return Book");
            System.out.println("6. Delete Book");
            System.out.println("7. Exit");
            System.out.print("Choose an option: ");

            String choice = scanner.nextLine().trim();

            switch (choice) {
                case "1": addBook(); break;
                case "2": viewBooks(); break;
                case "3": searchBook(); break;
                case "4": issueBook(); break;
                case "5": returnBook(); break;
                case "6": deleteBook(); break;
                case "7":
                    saveBooks();
                    System.out.println("Library data saved. Goodbye!");
                    running = false;
                    break;
                default:
                    System.out.println("Invalid option. Try again.");
            }
        }
    }

    static void addBook() {
        System.out.print("Enter book title: ");
        String title = scanner.nextLine().trim();
        System.out.print("Enter author name: ");
        String author = scanner.nextLine().trim();

        int newId = books.isEmpty() ? 1 : books.get(books.size() - 1).id + 1;
        books.add(new Book(newId, title, author, false));
        saveBooks();
        System.out.println("Book added successfully with ID " + newId + ".");
    }

    static void viewBooks() {
        if (books.isEmpty()) {
            System.out.println("No books in the library yet.");
            return;
        }
        System.out.println("\nID  | Title                | Author               | Status");
        System.out.println("----------------------------------------------------------------");
        for (Book b : books) {
            System.out.printf("%-4d| %-21s| %-21s| %s%n",
                    b.id, b.title, b.author, b.issued ? "Issued" : "Available");
        }
    }

    static void searchBook() {
        System.out.print("Enter title keyword to search: ");
        String keyword = scanner.nextLine().trim().toLowerCase();
        boolean found = false;

        for (Book b : books) {
            if (b.title.toLowerCase().contains(keyword)) {
                System.out.printf("Found: [ID %d] %s by %s - %s%n",
                        b.id, b.title, b.author, b.issued ? "Issued" : "Available");
                found = true;
            }
        }
        if (!found) System.out.println("No matching books found.");
    }

    static void issueBook() {
        System.out.print("Enter book ID to issue: ");
        int id = readInt();
        Book b = findBook(id);
        if (b == null) {
            System.out.println("Book not found.");
        } else if (b.issued) {
            System.out.println("This book is already issued.");
        } else {
            b.issued = true;
            saveBooks();
            System.out.println("Book \"" + b.title + "\" issued successfully.");
        }
    }

    static void returnBook() {
        System.out.print("Enter book ID to return: ");
        int id = readInt();
        Book b = findBook(id);
        if (b == null) {
            System.out.println("Book not found.");
        } else if (!b.issued) {
            System.out.println("This book was not issued.");
        } else {
            b.issued = false;
            saveBooks();
            System.out.println("Book \"" + b.title + "\" returned successfully.");
        }
    }

    static void deleteBook() {
        System.out.print("Enter book ID to delete: ");
        int id = readInt();
        Book b = findBook(id);
        if (b == null) {
            System.out.println("Book not found.");
        } else {
            books.remove(b);
            saveBooks();
            System.out.println("Book deleted successfully.");
        }
    }

    static Book findBook(int id) {
        for (Book b : books) {
            if (b.id == id) return b;
        }
        return null;
    }

    static int readInt() {
        try {
            return Integer.parseInt(scanner.nextLine().trim());
        } catch (NumberFormatException e) {
            return -1;
        }
    }

    static void saveBooks() {
        try (PrintWriter writer = new PrintWriter(new FileWriter(FILE_NAME))) {
            for (Book b : books) {
                writer.println(b.toFileLine());
            }
        } catch (IOException e) {
            System.out.println("Error saving library data: " + e.getMessage());
        }
    }

    static void loadBooks() {
        File file = new File(FILE_NAME);
        if (!file.exists()) return;

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line;
            while ((line = reader.readLine()) != null) {
                if (!line.isBlank()) {
                    books.add(Book.fromFileLine(line));
                }
            }
        } catch (IOException e) {
            System.out.println("Error loading library data: " + e.getMessage());
        }
    }
}
