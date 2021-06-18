package design;

import team.*;

import java.util.List;

import java.io.FileOutputStream;
import java.util.Date;
import com.itextpdf.text.*;
import com.itextpdf.text.pdf.*;

//первым делом выводить инфромацию о команде в целом
//потом таблицу игроков
//а затем таблицу календаря
/**
 * Класс для создания PDF отчета
 * @param FILE Путь файла, куда записывать
 * @param FONT Путь файла с нужным шрифтом для отображения русского языка
 * @param bf Вспомогательная переменная для FONT
 * @param rus_font Русский шрифт
 * @param document Объект документа 
 */
public class PDFGenerator
{
    private String FILE;
    public static final String FONT = "./src/main/resources/fonts/times.ttf";
    private BaseFont bf;
    Font rus_font;
    private Document document;
    
    /**
     * 
     * @param path Путь сохранения файла
     * @param msg Выводимое сообщение о команде
     */
    public PDFGenerator(String path, String msg)
    {
        this.FILE = path;
        try
        {
            document = new Document();
            PdfWriter.getInstance(document, new FileOutputStream(FILE));//получения экземляра класса PdfWriter
            document.open();
            addMetaData();
            addTitle(msg);
            bf=BaseFont.createFont(FONT, BaseFont.IDENTITY_H, BaseFont.EMBEDDED);
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    private void addMetaData()
    {
        document.addTitle("Генерация отчета");
        document.addSubject("С использованием iTextPDF");
        document.addAuthor("sedub01");
        document.addCreator("Это тоже я!");
    }

    //Добавляем титульную страницу с датой отчета
    private void addTitle(String msg)
    {
        try{
            bf=BaseFont.createFont(FONT, BaseFont.IDENTITY_H, BaseFont.EMBEDDED);
            Paragraph preface = new Paragraph();
            Font rus_font = new Font(bf, 18, Font.NORMAL);
            addEmptyLine(preface, 1);
            preface.add(new Paragraph("Команда \"theBest\"", rus_font));
            addEmptyLine(preface, 1);
            preface.add(new Paragraph("Отчет сгенерирован " + new Date(), rus_font));
            preface.add(new Paragraph(msg, rus_font));
            try
            {
                document.add(preface);
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
            document.newPage();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }

    }

    //Добавляем таблицу футболистов
    public void addFootballers(Team theBest)
    {
        Font font = new Font(bf, 12, Font.NORMAL);
        Paragraph ph = new Paragraph("1. Игроки", font);
        addEmptyLine(ph, 1);

        PdfPTable table = new PdfPTable(8);
        try{ 
            table.setTotalWidth(1650);
            table.setWidths(new int[]{150, 200, 300, 200, 150, 300, 150, 200}); 
        }
        catch(Exception e){e.getStackTrace();}
        
        PdfPCell pfpc;
        pfpc = new PdfPCell(new Phrase("ID", font));
        pfpc.setHorizontalAlignment(Element.ALIGN_CENTER);
        table.addCell(pfpc);
        pfpc = new PdfPCell(new Phrase("Имя", font));
        pfpc.setHorizontalAlignment(Element.ALIGN_CENTER);
        table.addCell(pfpc);
        pfpc = new PdfPCell(new Phrase("Фамилия", font));
        pfpc.setHorizontalAlignment(Element.ALIGN_CENTER);
        table.addCell(pfpc);
        pfpc = new PdfPCell(new Phrase("Специализация", font));
        pfpc.setHorizontalAlignment(Element.ALIGN_CENTER);
        table.addCell(pfpc);
        pfpc = new PdfPCell(new Phrase("Клуб", font));
        pfpc.setHorizontalAlignment(Element.ALIGN_CENTER);
        table.addCell(pfpc);
        pfpc = new PdfPCell(new Phrase("Город", font));
        pfpc.setHorizontalAlignment(Element.ALIGN_CENTER);
        table.addCell(pfpc);
        pfpc = new PdfPCell(new Phrase("Голы", font));
        pfpc.setHorizontalAlignment(Element.ALIGN_CENTER);
        table.addCell(pfpc);
        pfpc = new PdfPCell(new Phrase("Зарплата", font));
        pfpc.setHorizontalAlignment(Element.ALIGN_CENTER);
        table.addCell(pfpc);

        theBest.addCells(table, font);
        
        table.setHeaderRows(1);
        ph.add(table);
        try
        {
            document.add(ph);
            document.newPage();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    /**
     * Добавляем таблицу дат
     * @param calendar Лист с датами
     */
    public void addCals(List<Calendar> calendar)
    {
        Font font = new Font(bf, 12, Font.NORMAL);
        Paragraph ph = new Paragraph("2. Календарь", font);
        addEmptyLine(ph, 1);

        PdfPTable table = new PdfPTable(3);
        PdfPCell pfpc;
        pfpc = new PdfPCell(new Phrase("Дата", font));
        pfpc.setHorizontalAlignment(Element.ALIGN_CENTER);
        table.addCell(pfpc);
        pfpc = new PdfPCell(new Phrase("Счет сборной", font));
        pfpc.setHorizontalAlignment(Element.ALIGN_CENTER);
        table.addCell(pfpc);
        pfpc = new PdfPCell(new Phrase("Счет противника", font));
        pfpc.setHorizontalAlignment(Element.ALIGN_CENTER);
        table.addCell(pfpc);

        for (Calendar cal: calendar){
            table.addCell(cal.getDate());
            table.addCell(""+cal.getWins());
            table.addCell(""+cal.getLosses());
        }

        table.setHeaderRows(1);
        ph.add(table);
        try
        {
            document.add(ph);
            document.newPage();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    //Добавляем пустые строки
    private static void addEmptyLine(Paragraph paragraph, int number) {
        for (int i = 0; i < number; i++) {
            paragraph.add(new Paragraph(" "));
        }
    }

    public void doClose()
    {
        document.close();
    }
}