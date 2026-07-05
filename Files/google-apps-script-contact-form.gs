/**
 * Portfolio Contact Form Handler
 * ------------------------------
 * This script runs inside a Google Sheet's Apps Script editor.
 * It receives POST requests from the portfolio contact form,
 * logs each submission as a new row in the sheet, and sends
 * an email notification to you.
 *
 * SETUP INSTRUCTIONS:
 * 1. Go to https://sheets.google.com and create a new blank spreadsheet.
 *    Name it something like "Portfolio Messages".
 * 2. In the sheet, click Extensions > Apps Script.
 * 3. Delete any starter code in the editor, then paste this entire file in.
 * 4. Change the RECIPIENT_EMAIL constant below to your real email address.
 * 5. Click Deploy > New deployment.
 *    - Click the gear icon next to "Select type" and choose "Web app".
 *    - Description: "Contact Form Handler" (or anything).
 *    - Execute as: Me.
 *    - Who has access: Anyone.
 *    - Click Deploy.
 * 6. Google will ask you to authorize the script — click Authorize access,
 *    choose your account, click Advanced > Go to (project name), then Allow.
 * 7. Copy the "Web app URL" it gives you (ends in /exec).
 * 8. Paste that URL into the `scriptURL` variable in index.html's sendMessage() function.
 *
 * Every time someone submits your contact form, a new row will appear in this
 * sheet with the timestamp, name, email, and message — and you'll get an email too.
 */

const RECIPIENT_EMAIL = "example@email.com"; // <-- change this to your real email
const SHEET_NAME = "Messages";

function doPost(e) {
  try {
    const sheet = getOrCreateSheet();
    const data = JSON.parse(e.postData.contents);

    const name = data.name || "";
    const email = data.email || "";
    const message = data.message || "";
    const timestamp = new Date();

    if (!name || !email || !message) {
      return jsonResponse({ result: "error", message: "Missing required fields." });
    }

    sheet.appendRow([timestamp, name, email, message]);

    sendNotificationEmail(name, email, message);

    return jsonResponse({ result: "success" });
  } catch (err) {
    return jsonResponse({ result: "error", message: err.toString() });
  }
}

function getOrCreateSheet() {
  const ss = SpreadsheetApp.getActiveSpreadsheet();
  let sheet = ss.getSheetByName(SHEET_NAME);

  if (!sheet) {
    sheet = ss.insertSheet(SHEET_NAME);
    sheet.appendRow(["Timestamp", "Name", "Email", "Message"]);
    sheet.setFrozenRows(1);
  }

  return sheet;
}

function sendNotificationEmail(name, email, message) {
  const subject = "New message from " + name + " via portfolio site";
  const body =
    "You received a new message from your portfolio contact form.\n\n" +
    "Name: " + name + "\n" +
    "Email: " + email + "\n\n" +
    "Message:\n" + message;

  MailApp.sendEmail(RECIPIENT_EMAIL, subject, body, {
    replyTo: email
  });
}

function jsonResponse(obj) {
  return ContentService
    .createTextOutput(JSON.stringify(obj))
    .setMimeType(ContentService.MimeType.JSON);
}
