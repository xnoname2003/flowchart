# KERJAIN YAK SESUAI LANGKAH-LANGKAH NYA!

1. Git pull main jangan lupa 
    ```
    git pull origin main
    ```
    <img width="674" height="102" alt="image" src="https://github.com/user-attachments/assets/f31f37b7-d3a6-4a1c-86bd-94ebe5954ef4" />
2. Checkout Branch buat bikin branch baru
    ```
    git checkout -b revalina-sales-report
    ```
    <img width="612" height="115" alt="image" src="https://github.com/user-attachments/assets/976f2544-f492-48dd-a6c7-7a6c29550548" />
3. Git pull main lagi buat mastiin branch baru udah ter-update
    ```
    git pull origin main
    ```
    <img width="674" height="102" alt="image" src="https://github.com/user-attachments/assets/f31f37b7-d3a6-4a1c-86bd-94ebe5954ef4" />
4. Install library yang dibutuhkan
    ```
    npm install
    ```
    ```
    composer require maatwebsite/excel
    ```
    ```
    composer install
    ```
5. Buat Folder `Export` pada path `app/Filament`

    <img width="405" height="208" alt="image" src="https://github.com/user-attachments/assets/5a1523c9-0748-4142-abb9-dbfcc9800f66" />
6. Buat file `StyledExcelExport.php` dan `TransactionReportExport.php` pada folder `Export` di path `app/Filament/Exports`
    <img width="402" height="207" alt="image" src="https://github.com/user-attachments/assets/02059bfd-5899-482d-a691-82ed31de061a" />
7. Copy code berikut pada file `StyledExcelExport.php`
    ```
    <?php

    namespace App\Filament\Exports;

    use Maatwebsite\Excel\Events\AfterSheet;
    use pxlrbt\FilamentExcel\Exports\ExcelExport;

    class StyledExcelExport extends ExcelExport
    {
        public function registerEvents(): array
        {
            // Ambil event yang sudah ada dari parent class (jika ada)
            $parentEvents = parent::registerEvents();

            // Gabungkan event parent dengan event styling kustom kita
            return array_merge($parentEvents, [
                AfterSheet::class => function(AfterSheet $event) {
                    $sheet = $event->sheet->getDelegate();

                    // 1. Atur style untuk header (baris pertama)
                    $sheet->getStyle('A1:' . $sheet->getHighestColumn() . '1')->applyFromArray([
                        'font' => [
                            'bold' => true,
                            'color' => ['rgb' => 'FFFFFF'],
                        ],
                        'fill' => [
                            'fillType' => \PhpOffice\PhpSpreadsheet\Style\Fill::FILL_SOLID,
                            'startColor' => ['rgb' => '3B82F6'], // Warna Biru
                        ],
                    ]);

                    // 2. Tambahkan border ke seluruh tabel
                    $range = 'A1:' . $sheet->getHighestColumn() . $sheet->getHighestRow();
                    $sheet->getStyle($range)->getBorders()->getAllBorders()->setBorderStyle(\PhpOffice\PhpSpreadsheet\Style\Border::BORDER_THIN);

                    // 3. Atur auto-size untuk setiap kolom
                    foreach (range('A', $sheet->getHighestColumn()) as $columnID) {
                        $sheet->getColumnDimension($columnID)->setAutoSize(true);
                    }
                }
            ]);
        }
    }
    ```
8. Copy code berikut pada file `TransactionReportExport.php`
    ```
    <?php

    namespace App\Filament\Exports;

    use Illuminate\Contracts\View\View;
    use Illuminate\Database\Eloquent\Builder;
    use Illuminate\Support\Carbon;
    use Maatwebsite\Excel\Concerns\FromView;
    use Maatwebsite\Excel\Concerns\ShouldAutoSize;
    use Maatwebsite\Excel\Concerns\WithEvents;
    use Maatwebsite\Excel\Concerns\WithTitle;
    use Maatwebsite\Excel\Events\AfterSheet;
    use PhpOffice\PhpSpreadsheet\Style\Alignment;
    use PhpOffice\PhpSpreadsheet\Style\Border;
    use PhpOffice\PhpSpreadsheet\Style\Fill;
    use PhpOffice\PhpSpreadsheet\Style\NumberFormat;

    class TransactionReportExport implements FromView, WithTitle, ShouldAutoSize, WithEvents
    {
        public function __construct(
            public Builder $query,
            protected string $format = 'pdf',
            protected ?string $startDate = null,
            protected ?string $endDate = null
        ) {
            //
        }

        public function view(): View
        {
            $rows = $this->query->with(['user', 'payments'])->get();

            $totalSales = $rows->sum('total');

            $startDate = $this->startDate
                ? Carbon::parse($this->startDate)->format('d M Y')
                : ($rows->isNotEmpty() ? $rows->last()->created_at->format('d M Y') : 'N/A');
            $endDate = $this->endDate
                ? Carbon::parse($this->endDate)->format('d M Y')
                : ($rows->isNotEmpty() ? $rows->first()->created_at->format('d M Y') : 'N/A');

            return view('exports.transaction-report', [
                'rows' => $rows,
                'totalSales' => $totalSales,
                'startDate' => $startDate,
                'endDate' => $endDate,
                'isExcel' => $this->format === 'xlsx',
            ]);
        }

        /**
        * @return string
        */
        public function title(): string
        {
            return 'Laporan Penjualan';
        }

        public function registerEvents(): array
        {
            return [
                AfterSheet::class => function (AfterSheet $event) {
                    $sheet = $event->sheet->getDelegate();
                    $highestRow = $sheet->getHighestRow();
                    $highestColumn = $sheet->getHighestColumn();

                    $headerRow = null;
                    for ($row = 1; $row <= $highestRow; $row++) {
                        $value = (string) $sheet->getCell("A{$row}")->getValue();
                        if (trim($value) === 'Tanggal') {
                            $headerRow = $row;
                            break;
                        }
                    }

                    $headerRow ??= 1;
                    $tableRange = "A{$headerRow}:{$highestColumn}{$highestRow}";
                    $footerRow = $highestRow;
                    for ($row = $highestRow; $row >= $headerRow; $row--) {
                        $value = (string) $sheet->getCell("A{$row}")->getValue();
                        if (trim($value) === 'Total Penjualan') {
                            $footerRow = $row;
                            break;
                        }
                    }

                    $sheet->getStyle("A{$headerRow}:{$highestColumn}{$headerRow}")->applyFromArray([
                        'font' => [
                            'bold' => true,
                            'color' => ['rgb' => 'FFFFFF'],
                        ],
                        'fill' => [
                            'fillType' => Fill::FILL_SOLID,
                            'startColor' => ['rgb' => '1F2937'],
                        ],
                        'alignment' => [
                            'horizontal' => Alignment::HORIZONTAL_LEFT,
                            'vertical' => Alignment::VERTICAL_CENTER,
                        ],
                    ]);

                    $sheet->getStyle("A{$footerRow}:{$highestColumn}{$footerRow}")->applyFromArray([
                        'font' => [
                            'bold' => true,
                            'color' => ['rgb' => 'FFFFFF'],
                        ],
                        'fill' => [
                            'fillType' => Fill::FILL_SOLID,
                            'startColor' => ['rgb' => '1F2937'],
                        ],
                        'alignment' => [
                            'horizontal' => Alignment::HORIZONTAL_LEFT,
                            'vertical' => Alignment::VERTICAL_CENTER,
                        ],
                    ]);

                    $sheet->getStyle($tableRange)->getBorders()->getAllBorders()
                        ->setBorderStyle(Border::BORDER_THIN);

                    $sheet->getStyle($tableRange)->getAlignment()->setVertical(Alignment::VERTICAL_TOP);
                    $sheet->setAutoFilter($tableRange);
                    $sheet->freezePane('A' . ($headerRow + 1));

                    $sheet->getColumnDimension('A')->setWidth(20);
                    $sheet->getColumnDimension('B')->setWidth(34);
                    $sheet->getColumnDimension('C')->setWidth(20);
                    $sheet->getColumnDimension('D')->setWidth(12);
                    $sheet->getColumnDimension('E')->setWidth(12);
                    $sheet->getColumnDimension('F')->setWidth(16);

                    if ($this->format === 'xlsx') {
                        $sheet->getStyle("F" . ($headerRow + 1) . ":F{$highestRow}")
                            ->getNumberFormat()
                            ->setFormatCode(NumberFormat::FORMAT_NUMBER_COMMA_SEPARATED1);
                    }
                },
            ];
        }
    }
    ```
9. Ubah semua code pada file `TransactionResource.php` (`app/Filament/Resources/TransactionResource.php`) seperti di bawah ini
    <img width="417" height="476" alt="image" src="https://github.com/user-attachments/assets/187a1972-b520-4ce7-9495-a2ec9205c8fa" />

    ```
    <?php

    namespace App\Filament\Resources;

    use App\Filament\Resources\TransactionResource\Pages;
    use App\Filament\Resources\TransactionResource\RelationManagers;
    use App\Models\Transaction;
    use Filament\Forms;
    use Filament\Forms\Form;
    use Filament\Resources\Resource;
    use Filament\Tables;
    use Filament\Tables\Table;
    use Illuminate\Database\Eloquent\Builder;
    use Illuminate\Database\Eloquent\SoftDeletingScope;
    use Filament\Tables\Actions\Action;
    use App\Filament\Pages\DetailOrder;
    use Filament\Notifications\Notification;
    use Illuminate\Support\Facades\DB;
    use Illuminate\Support\Str;
    use App\Filament\Exports\TransactionReportExport;
    use Filament\Tables\Contracts\HasTable;
    use Maatwebsite\Excel\Facades\Excel;
    use Maatwebsite\Excel\Excel as ExcelWriter;

    class TransactionResource extends Resource
    {
        protected static ?string $model = Transaction::class;

        protected static ?string $navigationIcon = 'heroicon-o-rectangle-stack';
        protected static ?string $navigationGroup = 'Menu Transactions';

        public static function form(Form $form): Form
        {
            return $form
                ->schema([
                    Forms\Components\Select::make('user_id')
                        ->label('User')
                        ->relationship('user', 'name')
                        ->searchable()
                        ->required(),

                    Forms\Components\TextInput::make('invoice')
                        ->label('Invoice')
                        ->disabled()
                        ->required(),

                    Forms\Components\Select::make('status')
                        ->label('Status')
                        ->options([
                            'pending'   => 'Pending',
                            'paid'      => 'Paid',
                            'completed' => 'Completed',
                            'cancelled' => 'Cancelled',
                        ])
                        ->required(),

                    Forms\Components\TextInput::make('total')
                        ->label('Total')
                        ->numeric()
                        ->disabled(),

                    Forms\Components\TextInput::make('paid_amount')
                        ->label('Pembayaran')
                        ->numeric()
                        ->disabled(),

                    Forms\Components\TextInput::make('change_amount')
                        ->label('Kembalian')
                        ->numeric()
                        ->disabled(),
                ]);
        }

        public static function table(Table $table): Table
        {
            return $table
                ->columns([
                    Tables\Columns\TextColumn::make('invoice')
                        ->label('Invoice')
                        ->searchable()
                        ->sortable(),

                    Tables\Columns\TextColumn::make('user.name')
                        ->label('User')
                        ->sortable()
                        ->searchable(),

                    Tables\Columns\TextColumn::make('status')
                        ->label('Status')
                        ->badge()
                        ->color(fn (string $state): string => match ($state) {
                            'pending' => 'warning',
                            'paid' => 'success',
                            'completed' => 'success',
                            'cancelled'  => 'danger',
                        })
                        ->sortable(),

                    Tables\Columns\TextColumn::make('total')
                        ->label('Total')
                        ->money('idr')
                        ->sortable(),

                    Tables\Columns\TextColumn::make('paid_amount')
                        ->label('Pembayaran')
                        ->money('idr'),

                    Tables\Columns\TextColumn::make('change_amount')
                        ->label('Kembalian')
                        ->money('idr'),

                    Tables\Columns\TextColumn::make('created_at')
                        ->label('Tanggal')
                        ->dateTime('d M Y H:i')
                        ->sortable(),
                ])
                ->filters([
                    Tables\Filters\SelectFilter::make('status')
                        ->options([
                            'pending'   => 'Pending',
                            'paid'      => 'Paid',
                            'completed' => 'Completed',
                            'cancelled' => 'Cancelled',
                    ]),
                    Tables\Filters\Filter::make('date')
                        ->form([
                            Forms\Components\DatePicker::make('created_at')
                                ->label('Tanggal Transaksi'),
                    ])
                        ->query(function ($query, array $data) {
                            return $query
                                ->when(
                                    $data['created_at'],
                                    fn ($query, $date) => $query->whereDate('created_at', $date),
                                );
                    }),
                        Tables\Filters\Filter::make('date_range')
                            ->form([
                                Forms\Components\DatePicker::make('from')->label('Dari'),
                                Forms\Components\DatePicker::make('until')->label('Sampai'),
                            ])
                            ->query(function ($query, array $data) {
                                return $query
                                    ->when(
                                        $data['from'],
                                        fn ($query, $date) => $query->whereDate('created_at', '>=', $date),
                                    )
                                    ->when(
                                        $data['until'],
                                        fn ($query, $date) => $query->whereDate('created_at', '<=', $date),
                                    );
                            }),

                ])
                ->headerActions([
                    Action::make('export_xlsx')
                        ->label('Export XLSX')
                        ->icon('heroicon-o-table-cells')
                        ->action(function (HasTable $livewire) {
                            $query = $livewire->getFilteredSortedTableQuery();
                            $filters = $livewire->tableFilters ?? [];
                            $startDate = data_get($filters, 'date_range.from')
                                ?? data_get($filters, 'date.created_at');
                            $endDate = data_get($filters, 'date_range.until')
                                ?? data_get($filters, 'date.created_at');
                            $filename = 'SalesReport-' . date('YmdHis') . '-' . Str::upper(Str::random(4)) . '.xlsx';

                            return Excel::download(
                                new TransactionReportExport($query, 'xlsx', $startDate, $endDate),
                                $filename,
                                ExcelWriter::XLSX
                            );
                        }),
                    Action::make('export_pdf')
                        ->label('Export PDF')
                        ->icon('heroicon-o-document-text')
                        ->action(function (HasTable $livewire) {
                            $query = $livewire->getFilteredSortedTableQuery();
                            $filters = $livewire->tableFilters ?? [];
                            $startDate = data_get($filters, 'date_range.from')
                                ?? data_get($filters, 'date.created_at');
                            $endDate = data_get($filters, 'date_range.until')
                                ?? data_get($filters, 'date.created_at');
                            $filename = 'SalesReport-' . date('YmdHis') . '-' . Str::upper(Str::random(4)) . '.pdf';

                            return Excel::download(
                                new TransactionReportExport($query, 'pdf', $startDate, $endDate),
                                $filename,
                                ExcelWriter::DOMPDF
                            );
                        }),
                        
                ])
                ->actions([
                    Tables\Actions\ViewAction::make()
                        ->url(fn (Transaction $record) => DetailOrder::getUrl(['invoice' => $record->invoice])),

                    Action::make('complete')
                        ->label('Selesaikan')
                        ->icon('heroicon-o-check-circle')
                        ->color('success')
                        ->requiresConfirmation()
                        ->modalHeading(fn (Transaction $record) => "Selesaikan Pesanan {$record->invoice}?")
                        ->action(function (Transaction $record) {
                            DB::transaction(function () use ($record) {
                                $record->update(['status' => 'completed']);
                                $record->payments()->where('transaction_id', $record->id)->update(['status' => 'completed']);
                            });

                            Notification::make()
                                ->title('Pesanan Telah Selesai')
                                ->success()
                                ->send();
                        })
                        ->visible(fn (Transaction $record): bool => $record->status === 'paid'),
                    
                    Action::make('print')
                        ->label('Print Struk')
                        ->icon('heroicon-o-printer')
                        ->url(fn ($record) => route('receipt.show', $record))
                        ->openUrlInNewTab(),

                    Tables\Actions\EditAction::make(),
                    Tables\Actions\DeleteAction::make(),
                ])
                ->bulkActions([
                    Tables\Actions\BulkActionGroup::make([
                        Tables\Actions\DeleteBulkAction::make(),
                    ]),
                ])
                ->defaultSort('created_at', 'desc');
        }

        public static function getRelations(): array
        {
            return [
                RelationManagers\ItemsRelationManager::class,
                RelationManagers\ToppingsRelationManager::class,
            ];
        }

        public static function getPages(): array
        {
            return [
                'index' => Pages\ListTransactions::route('/'),
                'edit' => Pages\EditTransaction::route('/{record}/edit'),
            ];
        }
    }
    ```
10. Buat folder `exports` pada path `resources/views`
    <img width="404" height="430" alt="image" src="https://github.com/user-attachments/assets/282dbd92-8cf6-425a-a45e-b24d1bf40564" />
11. Buat file `transaction-report.blade.php` pada folder `exports` pada path `resources/views`
    <img width="406" height="433" alt="image" src="https://github.com/user-attachments/assets/6cff1fdb-d923-4532-af1b-698159869e1d" />
12. Copy code dibawah ini ke dalam file `transaction-report.blade.php` (`resources/views/exports/transaction-report.blade.php`) yang telah dibuat
    ```
    <!DOCTYPE html>
    <html lang="id">
    <head>
        <meta charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
        <title>Laporan Penjualan Cafelora</title>
        <style>
            @page {
                size: A4 landscape;
                margin: 14mm;
            }
            body {
                margin: 0;
                padding: 0;
                font-family: Arial, sans-serif;
                color: #0f172a;
                background: #ffffff;
            }
            .container {
                width: 100%;
                max-width: 980px;
                margin: 0 auto;
                padding: 8px 0 12px;
            }
            .title {
                text-align: center;
                font-size: 16px;
                font-weight: 700;
                text-decoration: underline;
                margin-bottom: 8px;
            }
            .period {
                text-align: right;
                font-size: 10px;
                margin-bottom: 8px;
            }
            .table-wrap {
                border: 1px solid #cbd5e1;
            }
            table {
                width: 100%;
                border-collapse: collapse;
            }
            .header-table td {
                border: none;
            }
            .header-table,
            .header-table tbody,
            .header-table tr,
            .header-table td {
                border: 0;
            }
            thead th {
                background: #1f2937;
                color: #ffffff;
                font-size: 10px;
                font-weight: 600;
                padding: 6px 6px;
                border: 1px solid #334155;
                text-align: left;
            }
            tbody td {
                font-size: 10px;
                padding: 6px 6px;
                border: 1px solid #cbd5e1;
                vertical-align: top;
            }
            tbody tr:nth-child(even) {
                background: #f8fafc;
            }
            tfoot td {
                background: #1f2937;
                color: #ffffff;
                font-weight: 600;
                padding: 8px 6px;
                border: 1px solid #334155;
                font-size: 10px;
            }
            .text-center { text-align: center; }
            .text-right { text-align: right; }
            .nowrap { white-space: nowrap; }
            .badge {
                display: inline-block;
                padding: 2px 6px;
                border-radius: 999px;
                border: 1px solid;
                font-size: 9px;
                font-weight: 600;
            }
            .badge-completed { background: #d1fae5; color: #047857; border-color: #a7f3d0; }
            .badge-paid { background: #dbeafe; color: #1d4ed8; border-color: #bfdbfe; }
            .badge-pending { background: #fef3c7; color: #b45309; border-color: #fde68a; }
            .badge-cancelled { background: #f1f5f9; color: #334155; border-color: #e2e8f0; }
            .badge-qris { background: #e0e7ff; color: #4338ca; border-color: #c7d2fe; }
            .badge-cash { background: #f1f5f9; color: #334155; border-color: #e2e8f0; }
            .badge-debit { background: #cffafe; color: #0e7490; border-color: #a5f3fc; }
        </style>
    </head>
    <body>
    @php
        $rp = fn($n) => 'Rp' . number_format((float) $n, 0, ',', '.');

        $statusBadge = function ($status) {
            $status = strtolower((string) $status);
            if ($status === 'completed') return 'badge-completed';
            if ($status === 'paid') return 'badge-paid';
            if ($status === 'pending') return 'badge-pending';
            return 'badge-cancelled';
        };

        $methodBadge = function ($method) {
            $method = strtolower((string) $method);
            if ($method === 'qris') return 'badge-qris';
            if ($method === 'cash') return 'badge-cash';
            if ($method === 'debit') return 'badge-debit';
            return 'badge-cash';
        };
    @endphp

    <div class="container">
        <table class="header-table" style="width: 100%; border-collapse: collapse; border-spacing: 0; margin: 0 auto 6px;">
            <tr>
                <td colspan="6" style="text-align: center; font-size: 16px; font-weight: 700; text-decoration: underline; padding: 6px 0;">
                    Laporan Penjualan Cafelora
                </td>
            </tr>
            <tr>
                <td colspan="6" style="text-align: center; font-size: 10px; padding: 2px 0 10px;">
                    Periode:&nbsp;<strong>{{ $startDate }}</strong>&nbsp;sampai dengan&nbsp;<strong>{{ $endDate }}</strong>
                </td>
            </tr>
        </table>

        <div class="table-wrap" style="margin: 0 auto;">
            <table>
                <thead>
                    <tr>
                        <th class="nowrap" style="width: 160px;">Tanggal</th>
                        <th>Invoice</th>
                        <th style="width: 160px;">Kasir</th>
                        <th class="text-center" style="width: 110px;">Status</th>
                        <th class="text-center" style="width: 100px;">Metode</th>
                        <th class="text-right" style="width: 120px;">Total</th>
                    </tr>
                </thead>
                <tbody>
                    @forelse($rows as $row)
                        @php
                            $method = optional($row->payments->first())->payment_method;
                        @endphp
                        <tr>
                            <td class="nowrap">{{ $row->created_at->format('d M Y H:i') }}</td>
                            <td>{{ $row->invoice }}</td>
                            <td>{{ $row->user->name ?? 'N/A' }}</td>
                            <td class="text-center">
                                @if(!empty($isExcel))
                                    {{ $row->status }}
                                @else
                                    <span class="badge {{ $statusBadge($row->status) }}">{{ $row->status }}</span>
                                @endif
                            </td>
                            <td class="text-center">
                                @if(!empty($isExcel))
                                    {{ $method ?: 'n/a' }}
                                @else
                                    <span class="badge {{ $methodBadge($method) }}">{{ $method ?: 'n/a' }}</span>
                                @endif
                            </td>
                            <td class="text-right nowrap">
                                @if(!empty($isExcel))
                                    {{ (float) $row->total }}
                                @else
                                    {{ $rp($row->total) }}
                                @endif
                            </td>
                        </tr>
                    @empty
                        <tr>
                            <td colspan="6" class="text-center" style="padding: 16px;">
                                Belum ada transaksi.
                            </td>
                        </tr>
                    @endforelse
                </tbody>
                <tfoot>
                    <tr>
                        <td colspan="5">Total Penjualan</td>
                        <td class="text-right nowrap">
                            @if(!empty($isExcel))
                                {{ (float) $totalSales }}
                            @else
                                {{ $rp($totalSales) }}
                            @endif
                        </td>
                    </tr>
                </tfoot>
            </table>
        </div>
    </div>
    </body>
    </html>
    ```
13. Refresh projek di browser lalu ke menu `Transactions`, nanti ada tombol `Export Excel` dan `Export PDF`
    <img width="1470" height="924" alt="image" src="https://github.com/user-attachments/assets/63be36d4-9a2a-4963-b89a-8bd634baf4b0" />
14. Kalo error tanya guru besar gpt :)
