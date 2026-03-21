import java.util.Scanner;

class Student {
    private int rollNo;
    private String name;
    private int[] marks;

    // Overloaded Constructor 1: Default
    public Student() {
        this.rollNo = 0;
        this.name = "Unknown";
        this.marks = new int[0];
    }

    // Overloaded Constructor 2: Parameterized
    public Student(int rollNo, String name, int[] marks) {
        this.rollNo = rollNo;
        this.name = name;
        this.marks = marks;
    }

    // Calculate GPA (Assuming 5 subjects out of 100, scaling to a 10.0 GPA format)
    public double calculateGPA() {
        if (marks.length == 0)
            return 0.0;
        int totalMarks = 0;
        for (int mark : marks) {
            totalMarks += mark;
        }
        double percentage = (double) totalMarks / marks.length;
        return percentage / 10.0; // Converting percentage to a 10-point GPA scale
    }

    public void displayDetails() {
        System.out.printf("Roll No: %d | Name: %s | GPA: %.2f\n", rollNo, name, calculateGPA());
    }

    public String getName() {
        return name;
    }
}

public class StudentManagementSystem {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of students: ");
        int n = scanner.nextInt();

        // Array of objects
        Student[] students = new Student[n];

        for (int i = 0; i < n; i++) {
            System.out.println("\n--- Entering details for Student " + (i + 1) + " ---");
            System.out.print("Enter Roll No: ");
            int roll = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            System.out.print("Enter Name: ");
            String name = scanner.nextLine();

            System.out.print("Enter number of subjects: ");
            int subCount = scanner.nextInt();
            int[] marks = new int[subCount];

            for (int j = 0; j < subCount; j++) {
                System.out.print("Enter marks for subject " + (j + 1) + " (out of 100): ");
                marks[j] = scanner.nextInt();
            }

            // Storing the object in the array
            students[i] = new Student(roll, name, marks);
        }

        System.out.println("\n=== All Student Records ===");
        for (Student s : students) {
            s.displayDetails();
        }

        findTopper(students);

        scanner.close();
    }

    public static void findTopper(Student[] students) {
        if (students.length == 0)
            return;

        Student topper = students[0];
        for (int i = 1; i < students.length; i++) {
            if (students[i].calculateGPA() > topper.calculateGPA()) {
                topper = students[i];
            }
        }

        System.out.println("\n🏆 Top Student 🏆");
        System.out.println(
                "The topper is " + topper.getName() + " with a GPA of " + String.format("%.2f", topper.calculateGPA()));
    }
}
