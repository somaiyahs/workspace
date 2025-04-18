create table categories(
name varchar(50) primary key
);

CREATE TABLE accounts (
name varchar(50) primary key,
balance decimal(10,2) not null
);

create table transactions (
id int auto_increment primary key, 
date DATE not null, 
merchant_name varchar(100), 
amount decimal(10,2) not null, 
account_id varchar(50) not null, 
category_id varchar(50) not null,
notes TEXT, 
document_linke varchar(255), 
foreign key (account_id) references accounts(name),
foreign key (category_id) references categories(name)
);