#pragma once
#include "Functions.h"
#include <msclr\marshal_cppstd.h>

namespace Client {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ BestStudentsForm
	/// </summary>
	public ref class BestStudentsForm : public System::Windows::Forms::Form
	{
	public:
		BestStudentsForm(Gasket& maindb)
		{
			InitializeComponent();
			DataGridViewColumn^ c = gcnew DataGridViewColumn();
			DataGridViewCell^ td = gcnew DataGridViewTextBoxCell();
			c->HeaderText = "ќценка";
			c->Name = "Column" + (dataGridView1->ColumnCount + 1);
			c->CellTemplate = td;
			dataGridView1->Columns->Add(c);
			multiset<Child*, CompSet> alpha;
			maindb.medalStudents(alpha);
			for (multiset<Child*>::const_iterator i = alpha.begin(); i != alpha.end(); ++i) {
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

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~BestStudentsForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	protected:
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
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(12, 12);
			this->dataGridView1->MultiSelect = false;
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->Size = System::Drawing::Size(368, 273);
			this->dataGridView1->TabIndex = 0;
			// 
			// BestStudentsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(392, 297);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"BestStudentsForm";
			this->Text = L"ћедалисты";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
};
}
