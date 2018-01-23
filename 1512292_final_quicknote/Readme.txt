Thông tin cá nhân
ID: 1512292
Name: Châu Hoàng Long
Email: chauhoaglong@gmail.com

Project: Ðồ án môn học lập trình window 2017-2018
QuickNote:

Main functions
	+ User press a shortcut key (any key combination as you wish, for example Windows + Space), a dialog will appear. Two textboxes are there: a textbox for typing the note and the other for tags.
	+ User types the note, enter multiple tags, seperated by commas and space (“, ”) then click Save. (For example: “test, study, info, todo”)
	+ User can browse through all the notes or browse by tags.
	+ Do statistics and draw chart based on tags and the number of corresponding notes.

Basic main success scenario flow
1. User launches the app. An icon  will be added to notification area
	+ User can right click on it to see menu: View notes, View statitistics, Exit.
- Exit menu, of course, will exit the app.
- View notes: A listbox / tree view will display all the tags, each tag has the number of notes corresponding with it.
When click on a tag, a list of all notes will be displayed briefly (around first 50 characters for preview) in a listbox or listview. points)
When click on an item on listbox / listview, the full content of the note will appear on a dialog or textbox.
- View statistics: Display chart based on tags and number of corresponding notes.
2. User presses the shortcut key (like Windows + Space), a dialog will appear for user to type the note, enter multiple tags, seperated by commas (“,”) then click Save.



Main flow:Khởi Ðộng chương trình.
Chương trình tự động cài đặt hook và cài đặt icon xuống thanh taskbar.
Khi bấm tổ hợp phím Ctrl + Space. Sẽ tiến hành bật hoặc tắt dialog nhanh.
Dialog dùng để ghi note nhanh.
Hoặc có thể bấm chuột phải vào QuickNote-> AddNote trên menu để mở Dialog thêm Note
Icon ở thanh taskbar có thể chuột phải chọn xem note hoặc xem biểu đồ.
1) Dialog: Cho phép nhập các tag và ngăn cách bằng dấu phẩy và có khoảng trắng, nếu nhập sai sẽ thông báo lỗi.
Bạn có thể nhập thông tin của note tùy ý.
Sau đó lưu lại bằng Buttuon Save và thông tin được lưu xuống file.

2) Sau khi đã có note thì bạn có thể chọn phải chuột Icon ở taskbar:
+ Bấm xem các note thì sẽ hiện ra danh sách tất cả các tag bạn đã tạo và số lần xuất hiện cửa tag đó trong note.
  Bấm vào một tag sẽ hiện ra tất cả các note thuộc tag đó.
  Bấm vào một note sẽ hiện thông tin của note lên textview.
  Có thể sửa chữa nội dung của note và nhấn save
+ Bấm xem biểu đồ thì chương trình sẽ vẽ biểu đồ tương ứng với số lần của tag xuất hiện ở các note.
  Vì số lượng note không kiểm soát hết được nên chỉ ràng buộc vẽ biểu đồ với 6 tag nếu lớn hơn thì sẽ chỉ chọn những tag có số lần xuất hiện nhiều hơn còn những tag còn lại sẽ được gộp chung thành một vùng trên biểu đồ.
+ Bấm chọn time note để xem các note theo thời gian

Khi tắt chương trình sẽ gỡ hook và gõ Icon trên taskbar.
Và mở lại chương trình sẽ đọc dữ liệu từ file đã có và có thể xem note và xem biểu đồ tần xuất của note.
Chuong trình được viết trên môi trường Microsoft Visual Studio Professional 2015 và ngôn ngữ C++.
Link youtube: https://youtu.be/aj-SulI1VjU
Link bitbucket: bitbucket.org/account/signin/?next=/chauhoaglong/windev/src
