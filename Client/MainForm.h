#include "Functions.h"
#include <msclr\marshal_cppstd.h>
#pragma once

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			maindb = new DB();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
			delete maindb;
		}
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;
	protected:
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker2;
	private: System::Windows::Forms::DataGridView^ dataGridView1;

	protected:
	private: DB* maindb;
	private: int selectedclass = 0;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->dateTimePicker2 = (gcnew System::Windows::Forms::DateTimePicker());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Location = System::Drawing::Point(72, 12);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(200, 20);
			this->dateTimePicker1->TabIndex = 0;
			this->dateTimePicker1->ValueChanged += gcnew System::EventHandler(this, &MainForm::dateTimePicker_ValueChanged);
			// 
			// dateTimePicker2
			// 
			this->dateTimePicker2->Location = System::Drawing::Point(72, 38);
			this->dateTimePicker2->Name = L"dateTimePicker2";
			this->dateTimePicker2->Size = System::Drawing::Size(200, 20);
			this->dateTimePicker2->TabIndex = 1;
			this->dateTimePicker2->ValueChanged += gcnew System::EventHandler(this, &MainForm::dateTimePicker_ValueChanged);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(23, 77);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(765, 350);
			this->dataGridView1->TabIndex = 2;
			this->dataGridView1->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::dataGridView1_CellEndEdit);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(303, 27);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 3;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox1_SelectedIndexChanged);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(442, 27);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 4;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(823, 455);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->dateTimePicker2);
			this->Controls->Add(this->dateTimePicker1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		std::map<int, std::wstring> classlist = maindb->getClasses();
		comboBox1->Items->Add("¬се ученики");
		comboBox1->SelectedIndex = 0;
		for (std::map<int, std::wstring>::const_iterator i = classlist.begin(); i != classlist.end(); ++i) {
			comboBox1->Items->Add(msclr::interop::marshal_as<String^>((*i).second));
			comboBox1->Refresh();
		}
		dateTimePicker_ValueChanged(dataGridView1, gcnew EventArgs());
		MainForm::Update();
	}
	private: System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	
	}
	private: System::Void dateTimePicker_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		dataGridView1->Rows->Clear();
		dataGridView1->Columns->Clear();
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
			maindb->MakeViborka(selectedclass);
			std::map<int, Child*> students = maindb->getStudentsFromClass(selectedclass);
			for (std::map<int, Child*>::const_iterator i = students.begin(); i != students.end(); ++i) {
				DataGridViewRow^ r = gcnew DataGridViewRow();
				r->HeaderCell->Value = msclr::interop::marshal_as<String^>(i->second->getName());
				r->CreateCells(dataGridView1);
				array<String^>^ Values = gcnew array<String^>(dataGridView1->ColumnCount);
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
					std::vector<std::pair<double, int>> temp = (*i).second->getDateMarks(t1, t2 + 86399);
					for (int i = 0; i < temp.size(); ++i) {
						Values[i] = temp[i].first == 0 ? L"" : temp[i].first.ToString();
					}
				}
				r->SetValues(Values);
				dataGridView1->Rows->Add(r);
				dataGridView1->RowHeadersWidth = 100;
			}
		}
	}
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		selectedclass = comboBox1->SelectedIndex;
		dateTimePicker_ValueChanged(dataGridView1, gcnew EventArgs());
	}
private: System::Void dataGridView1_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e){
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
		maindb->deleteMark(msclr::interop::marshal_as<std::wstring>(this->dataGridView1->Rows[e->RowIndex]->HeaderCell->Value->ToString()), t);
	} else {
		try {
			System::Int32^ tryint;
			tryint = System::Convert::ToInt32(this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value);
			maindb->changeMark(msclr::interop::marshal_as<std::wstring>(this->dataGridView1->Rows[e->RowIndex]->HeaderCell->Value->ToString()), static_cast<int>(tryint), t);
		}
		catch (Exception^ ex) {
			if (this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value != "") {
				MessageBox::Show("¬ведите число целого типа");
			}
			this->dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = L"";
		}
	}
}
};
}
