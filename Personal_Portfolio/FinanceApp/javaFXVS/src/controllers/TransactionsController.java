package controllers;

import view.*;

import java.sql.Connection;
import java.sql.PreparedStatement;

public class TransactionsController {

    public void addTransaction(String date, String time, double amount) {
    String sql = "INSERT INTO Transactions(date, time, amount) VALUES (?, ?, ?)";
    try (Connection conn = Database.connect();
         PreparedStatement pstmt = conn.prepareStatement(sql)) {
        pstmt.setString(1, date);
        pstmt.setString(2, time);
        pstmt.setDouble(3, amount);
        pstmt.executeUpdate();

        System.out.println("Connection success");
    } catch (Exception e) {
        e.printStackTrace();
    }
}


}
