#pragma once
#include "BestStudentsForm.h"

namespace Client {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			gasket = Gasket::getInstance();
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
			delete gasket;
		}
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;
	protected:
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker2;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	protected:
	private: Gasket* gasket;
	private: int selectedclass = 0;
	private: int selectedsubject = 0;
	private: String^ finder = L"";
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker2 = (gcnew System::Windows::Forms::DateTimePicker());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->dateTimePicker1->Location = System::Drawing::Point(83, 14);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(123, 20);
			this->dateTimePicker1->TabIndex = 0;
			this->dateTimePicker1->ValueChanged += gcnew System::EventHandler(this, &MainForm::dateTimePicker_ValueChanged);
			// 
			// dateTimePicker2
			// 
			this->dateTimePicker2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->dateTimePicker2->Location = System::Drawing::Point(83, 40);
			this->dateTimePicker2->Name = L"dateTimePicker2";
			this->dateTimePicker2->Size = System::Drawing::Size(123, 20);
			this->dateTimePicker2->TabIndex = 1;
			this->dateTimePicker2->ValueChanged += gcnew System::EventHandler(this, &MainForm::dateTimePicker_ValueChanged);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->dataGridView1->Location = System::Drawing::Point(23, 77);
			this->dataGridView1->MultiSelect = false;
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
			this->dataGridView1->Size = System::Drawing::Size(765, 350);
			this->dataGridView1->TabIndex = 2;
			this->dataGridView1->UseWaitCursor = true;
			this->dataGridView1->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::dataGridView1_CellValueChanged);
			// 
			// comboBox1
			// 
			this->comboBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(257, 27);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(89, 21);
			this->comboBox1->TabIndex = 3;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox1_SelectedIndexChanged);
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->textBox1->Location = System::Drawing::Point(585, 26);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(107, 20);
			this->textBox1->TabIndex = 4;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox1_TextChanged);
			// 
			// button1
			// 
			this->button1->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->button1->Location = System::Drawing::Point(698, 24);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(90, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Медалисты";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// comboBox2
			// 
			this->comboBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(420, 27);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(106, 21);
			this->comboBox2->TabIndex = 6;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox2_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(27, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Дата №1";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(27, 46);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Дата №2";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(213, 30);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(38, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Класс";
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(362, 29);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(52, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Предмет";
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(540, 29);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(39, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Поиск";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(823, 455);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->dateTimePicker2);
			this->Controls->Add(this->dateTimePicker1);
			this->Name = L"MainForm";
			this->Text = L"Школьный журнал";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		vector<std::wstring>  classlist = gasket->getClasses();
		comboBox1->Items->Add("Все ученики");
		comboBox1->SelectedIndex = 0;
		for (vector<std::wstring>::iterator i = classlist.begin(); i != classlist.end(); ++i) {
			comboBox1->Items->Add(msclr::interop::marshal_as<String^>(*i));
		}
		comboBox1->Items->Add("Выпустившиеся");
		comboBox1->Refresh();
		vector<std::wstring> sublist = gasket->getSubject();
		for(vector<std::wstring>::iterator i = sublist.begin(); i != sublist.end(); ++i){
			comboBox2->Items->Add(msclr::interop::marshal_as<String^>(*i));
		}
		comboBox2->SelectedIndex = 0;
		comboBox2->Refresh();
		dateTimePicker_ValueChanged(dataGridView1, gcnew EventArgs());
		MainForm::Update();
	}
	private: System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	
	}
	private: System::Void dateTimePicker_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		dataGridView1->Rows->Clear();
		dataGridView1->Columns->Clear();
		if (selectedclass == -1) {
			DataGridViewColumn^ c = gcnew DataGridViewColumn();
			DataGridViewCell^ td = gcnew DataGridViewTextBoxCell();
			c->HeaderText = "Итоговая оценка";
			c->Name = "Column" + (dataGridView1->ColumnCount + 1);
			c->CellTemplate = td;
			dataGridView1->Columns->Add(c);
			vector<Child*> students = gasket->getGraduated();
			for (vector<Child*>::iterator i = students.begin(); i != students.end(); ++i) {
				DataGridViewRow^ r = gcnew DataGridViewRow();
				r->HeaderCell->Value = msclr::interop::marshal_as<String^>((*i)->getName());
				r->ReadOnly = 1;
				r->CreateCells(dataGridView1);
				cli::array<String^>^ Values = gcnew cli::array<String^>(dataGridView1->ColumnCount);
				Values[0] = (*i)->getMark().ToString();
				r->SetValues(Values);
				dataGridView1->Rows->Add(r);
				dataGridView1->RowHeadersWidth = 250;
			}
		}
		else {
			DateTime ld, rd;
			ld = dateTimePicker1->Value.Date;
			rd = dateTimePicker2->Value.Date;
			if (rd >= ld) {
				for (int i = 0; i < (ld == rd ? 1 : (rd - ld).Days + 1); ++i) {
					DataGridViewColumn^ c = gcnew DataGridViewColumn();
					DataGridViewCell^ td = gcnew DataGridViewTextBoxCell();
					c->HeaderText = (ld.AddDays(i)).ToShortDateString();
					c->Name = "Column" + (dataGridView1->ColumnCount + 1);
					c->CellTemplate = td;
					dataGridView1->Columns->Add(c);
				}
				DataGridViewColumn^ c = gcnew DataGridViewColumn();
				DataGridViewCell^ td = gcnew DataGridViewTextBoxCell();
				c->HeaderText = "Средняя оценка";
				c->Name = "Column" + (dataGridView1->ColumnCount + 1);
				c->CellTemplate = td;
				dataGridView1->Columns->Add(c);
				vector<Child*> students = gasket->getStudentsFromClass(selectedclass, msclr::interop::marshal_as<wstring>(finder->ToString()));
				for (vector<Child*>::iterator i = students.begin(); i != students.end(); ++i) {
					DataGridViewRow^ r = gcnew DataGridViewRow();
					r->HeaderCell->Value = msclr::interop::marshal_as<String^>((*i)->getName());
					r->CreateCells(dataGridView1);
					cli::array<String^>^ Values = gcnew cli::array<String^>(dataGridView1->ColumnCount);
					for (int j = 0; j < dataGridView1->ColumnCount; j++) {
						DateTime dt = ld;
						tm q = { 0 };
						q.tm_hour = dt.Hour;
						q.tm_min = dt.Minute;
						q.tm_sec = dt.Second;
						q.tm_year = dt.Year - 1900;
						q.tm_mon = dt.Month - 1;
						q.tm_mday = dt.Day;
						time_t t1 = _mkgmtime(&q);
						dt = rd;
						q = { 0 };
						q.tm_hour = dt.Hour;
						q.tm_min = dt.Minute;
						q.tm_sec = dt.Second;
						q.tm_year = dt.Year - 1900;
						q.tm_mon = dt.Month - 1;
						q.tm_mday = dt.Day;
						time_t t2 = _mkgmtime(&q);
						vector<pair<double, int>> temp((t2 + 86399 - t1) / 86399);
						(*i)->getDateMarks(temp, t1, t2 + 86399, selectedsubject + 1);
						double sum = 0;
						int count = 0;
						for (int k = 0; k < temp.size(); ++k) {
							Values[k] = temp[k].second == 0 ? L"" : temp[k].first.ToString();
							if (temp[k].second != 0) {
								sum += temp[k].first;
								count++;
							}
						}
						Values[temp.size()] = sum == 0 ? L"" : (round(sum / count * 100) / 100).ToString();
					}
					r->SetValues(Values);
					dataGridView1->Rows->Add(r);
					dataGridView1->RowHeadersWidth = 200;
				}
			}
		}
	}
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		if (comboBox1->Text->Equals("Выпустившиеся")) {
			selectedclass = -1;
		} else {
			selectedclass = comboBox1->SelectedIndex;
		}
		dateTimePicker_ValueChanged(dataGridView1, gcnew EventArgs());
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		finder = textBox1->Text;
		dateTimePicker_ValueChanged(dataGridView1, gcnew EventArgs());
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Client::BestStudentsForm best(*gasket);
		best.ShowDialog();
	}

	private: System::Void dataGridView1_CellValueChanged(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		DateTime dt = dateTimePicker1->Value.Date;
		tm q = { 0 };
		q.tm_hour = dt.Hour;
		q.tm_min = dt.Minute;
		q.tm_sec = dt.Second;
		q.tm_year = dt.Year - 1900;
		q.tm_mon = dt.Month - 1;
		q.tm_mday = dt.Day;
		time_t t = _mkgmtime(&q);
		t += 86400 * e->ColumnIndex;
		if (this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value == nullptr) {
			gasket->deleteMark(msclr::interop::marshal_as<std::wstring>(this->dataGridView1->Rows[e->RowIndex]->HeaderCell->Value->ToString()), t, selectedsubject + 1);
			dateTimePicker_ValueChanged(dataGridView1, gcnew EventArgs());
		}
		else {
			try {
				System::Int32^ tryint;
				tryint = System::Convert::ToInt32(this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value);
				if (*tryint >= 1 && *tryint <= 5) {
					gasket->changeMark(msclr::interop::marshal_as<std::wstring>(this->dataGridView1->Rows[e->RowIndex]->HeaderCell->Value->ToString()), static_cast<int>(tryint), t, selectedsubject + 1);
					dateTimePicker_ValueChanged(dataGridView1, gcnew EventArgs());
				}
				else {
					MessageBox::Show("Оценка может быть в диапазоне от 1 до 5");
					this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = L"";
				}
			}
			catch (Exception^ ex) {
				if (this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value != "") {
					MessageBox::Show("Введите число целого типа");
				}
				this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = L"";
			}
		}
	}
	private: System::Void comboBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		selectedsubject = comboBox2->SelectedIndex;
		dateTimePicker_ValueChanged(dataGridView1, gcnew EventArgs());
	}
};
}
