**Thông tin cá nhân**
ID: 1512292
Name: 	Châu Hoàng Long
Email: chauhoaglong@gmail.com

**Project:**
Chương trình thống kê chi tiêu hàng ngày. Chương trình có các chức năng sau
1. Thêm vào danh sách một mục chi.

	Gồm 3 thành phần: Loại chi tiêu, nội dung chi, số tiền.
	
	Ví dụ: Ăn uống, Ăn trưa, 15000.
	
	Loại chi tiêu chỉ gồm các loại sau đây: 
		+ Ăn uống, 
		+ Di chuyển (bus, xăng, taxi…), 
		+ Nhà cửa (tiền thuê nhà, nước, điện,…), 
		+ Xe cộ (xăng, vá xe, bảo dưỡng…), 
		+ Nhu yếu phẩm (xà bông, sữa tắm…), 
		+ Dịch vụ (intenet, thẻ cảo điện thoại…).
		
2.	Xem lại danh sách các mục chi của mình, lưu và nạp vào tập tin text.
3.	Khi chương trình chạy lên tự động nạp danh sách chi tiêu từ tập tin text lên và hiển thị(ListView)
4.	Khi chương trình thoát thì tự động lưu danh sách mới vào tập tin text.
5.	Vẽ biểu đồ nhằm biểu diễn trực quan tỉ lệ tiêu xài.
6.	Bảng chú giải về thông tin biểu đồ.

**Các chức năng thực hiện được.**
1. Thêm vào danh sách một mục chi.
2. Xem lại danh sách các mục chi của mình, lưu và nạp vào tập tin text.
3. Khi chương trình chạy lên tự động nạp danh sách chi tiêu từ tập tin text lên và hiển thị(ListView)
4. Khi chương trình thoát thì tự động lưu danh sách mới vào tập tin text.
5. Vẽ biểu đồ nhằm biểu diễn trực quan tỉ lệ tiêu xài.
6.Bảng chú giải về thông tin biểu đồ.

**Các chức năng thêm.**
Reset lại toàn bộ thông tin.
Chức năng Back (quay lại trạng thái trước đó (nếu có)) và Prev(đến trạng thái sau đó (nếu có))

**Hướng dẫn sử dụng**
A.Khởi động chương trình.-> Chọn loại chi tiêu(combobox) (phải chọn, không chọn báo lỗi)
Nhập nội dung chi tiêu(Không được bỏ trống nếu bỏ sẽ báo lỗi).
Nhập số tiền chi(Không được nhập chữ).
Sau đó chọn thêm , thông tin sẽ lưu vào listview. Chương trình tự động vẽ biểu đồ Pie chart và tính tổng số tiền chi.
Chương trình sẽ kết thúc khi người dùng muốn và thoát. Toàn bộ thông tin sẽ lưu vào file và khi khởi động lại chương trình sẽ load dữ liệu từ file thể hiện lên listview và tính tổng tiền chi, vễ biểu đồ.

Chương trình được viết trên môi trường Microsoft Visual Studio 2017.

**Link demo:** https://youtu.be/_iZrwMqbP8I
