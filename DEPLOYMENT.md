# Deploy Cafelora Agar diakses Publik

## A. Beli Hosting yang ada fitur SSH
1. Kami menggunakan [Anymhost](https://anymhost.id/), lalu pilih menu `Developer Hosting` 
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/6c284d04-cee0-42c3-b7fb-26e7ac6ad335" />
2. Kami pilih paket `Newbie` karena cukup untuk kebutuhan kami dan sudah dukung `SSH Access` dengan harga cuma Rp180.000/tahun dan sudah free domain
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/000ce229-6759-4148-822c-7e515b13c0c1" />
3. Selesaikan pembayaran hingga masuk ke client side dari hosting
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/6ca2be0f-1978-48e4-9506-20fb0479ffbd" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/6f31808c-f2a3-413b-9537-b8694c742ac5" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/760a9aee-5e1d-433f-aa70-2962d0f76932" />
---

## B. Setting Akses SSH ke Server
1. Masuk cPanel AnymHost.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/3fc2b5f9-e15b-4b36-abaa-696f4d3bac22" />
2. Buka `SSH Access` lalu `Manage SSH Keys`.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/f32c042e-ce39-40dc-a71d-4e1dfa61e4ee" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/4f648771-4411-41eb-9383-ad04e7c3894e" />
3. Generate a new key.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/bde0f011-6952-4e36-8770-4981e8814a77" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/da9583f6-f5cc-4c33-8519-0ff96b569c47" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/a05bfa37-666b-418d-aedd-d16d7267a888" />
4. Klik `Manage` pada public key lalu klik `Authorize`.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/852ffb24-5f30-4a6c-abfa-6cd734d7e2e9" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/c7fd22a5-98bc-4ff8-a3ea-4785050d2458" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/0d4b304c-a0bc-4ffe-b5cb-c810f2ccd028" />
5. Simpan `public keys` dan `private keys` di notepad agar tidak hilang.
---

## C. Setting Akses Database
1. Masuk cPanel Anymhost, lalu klik `Manage My Database`.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/82759c92-50c5-4b83-89b3-1e71302be3a7" />
2. Pada menu `Create New Database` isi kolom `New Database` untuk membuat database baru, kemudian klik `Create Database`.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/b7e36c54-aafa-4622-a2f2-223e26f34c1e" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/fd4ca541-d6e0-4cbf-b59f-f24982a0ad60" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/d1c21fb6-c330-477c-ade7-712511efbf61" />
3. Pada menu `Database Users`, isi kolom `Add New User` untuk membuat user baru yang mengakses database, jika sudah klik `Create User`.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/03c54edc-4281-436b-b6c8-dd9a451f6caa" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/566abbb3-a5b6-4c3b-b570-e7728d49b212" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/604af8fd-4d41-4292-bf66-06603f501a5f" />
4. Simpan `nama database`, `username` dan `password` users database di notepad agar tidak hilang.
5. Pada menu `Add User To Database` pilih pada kolom `User` dan `Database` sesuai dengan user dan database yang sudah dibuat untuk memberikan akses user ke database, jika sudah klik `Add`.
    <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/136dafd9-a21b-4e60-9a2e-f307031a8cda" />
6. Pilih privilage apa yang digunakan user pada database, jika sudah klik `Make Changes`.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/6f838e5d-d617-4e44-8c5d-b60a2853c494" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/f82e0d13-c57c-4295-a1bf-d509d3627459" />
---

## D. Setting Deploy Keys dan Personal Access Tokens(clasic) di GitHub
1. Klik `Settings` pada repo yang ingin di deploy.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/359ce66a-c87c-4dda-91aa-5121c07e5c83" />
2. Klik `Deploy keys` pada sidebar menu.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/ac4f2bf2-dfb9-4003-9bf1-66ab6f3b23f4" />
3. Klik `Add deploy key`.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/ca635235-e4bc-4b8e-954b-17dc396d0984" />
4. Masukan `Title` dan `Key` lalu klik `Add key`, untuk key copy `public keys` pada point **B.4**.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/02e8db95-058b-49ef-bce3-19c40133fccc" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/41675aba-3767-4e96-a356-4e6a86ae569c" />
---

## E. Setting Personal Access Tokens(clasic) di GitHub.
1. Klik `Settings` pada menu profile.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/47238b33-8e2a-4acb-9df7-43afe9097903" />
2. Klik `Developer Settings`.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/30ea6c15-bd0b-4b2f-a345-33d41dd5fd37" />
3. Klik `Personal access tokens` lalu klik  `Tokens (classic)`.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/d1388b10-cc09-4392-a8f3-b321edd26f50" />
4. Klik `Generete new token` lalu klik `Generate new token (classic)`.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/6e43afe6-f815-42a9-862f-a160c107b40e" />
5. Isi kolom `Note`, kemudian atur `Expiration`, lalu pilih `scopes` nya, kalau sudah klik `Generate token`.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/052a9c6d-205a-4aef-a6e1-1cba372830c9" />
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/8402147f-2e4e-42c3-acad-5ac9afba8bc3" />
6. Copy `personal access tokens (classic)` di notepad agar tidak hilang.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/57088197-2b3a-4e2c-9cae-f6a53ae7b4a6" />
---

## F. Remote server menggunakan SSH dan cloning project Cafelora di server
1. Tanyakan ke CS port berapa yang digunakan untuk akses ssh, Anymhost menggunakan port `6401`
2. Catat `User_CPanel`, `HOSTNAME_SERVER`, dan `PASSWORD_CPanel` di notepad.
   <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/b5aff8ea-dcb3-4c3f-a332-13840cfcea00" />
3. Buka `terminal` pada laptop, kemudian ketikan perintah berikut, jika sudah klik `enter`
   ```
   ssh -p PORT USER_CPanel@HOSTNAME_SERVER
   ```
   <img width="680" height="106" alt="image" src="https://github.com/user-attachments/assets/85fa0053-99b8-499c-8314-4b5a4ef44c96" />
4. Masukan password CPanel pada `terminal`, lalu klik `enter` nanti akan otomatis masuk ke server via `terminal`
   <img width="975" height="174" alt="image" src="https://github.com/user-attachments/assets/6fe14cf7-e5f4-4794-a1c2-0af0ece09d76" />
5. Setelah masuk ke server, ketikan perintah berikut untuk clone repository, jika sudah klik `enter`
   ```
   git clone https://<YOUR_PERSONAL_TOKENS>@github.com/<YOUR_USERNAME>/<YOUR_REPOSITORY>.git
   ```
   <img width="1421" height="104" alt="image" src="https://github.com/user-attachments/assets/2399042f-9728-43cc-879a-407d3b99451c" />
6. Ketikan perintah berikut untuk memastikan project cafelora sudah di clone
   ```
   dir
   ```
   <img width="1405" height="362" alt="image" src="https://github.com/user-attachments/assets/3a04d0ed-a9a2-4b93-ac84-1b709063f7f3" />
---

## G. 

   



